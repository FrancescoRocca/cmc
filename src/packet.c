#include "packet.h"

#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "debug.h"
#include "json.h"

static int _read_varint(const uint8_t **p) {
	int value = 0;
	int pos = 0;

	while (1) {
		uint8_t byte = **p;
		(*p)++;
		value |= (byte & SEGMENT_BITS) << pos;

		if ((byte & CONTINUE_BIT) == 0) {
			break;
		}

		pos += 7;
	}

	return value;
}

static int _varint_size(int value) {
	int size = 0;

	do {
		value >>= 7;
		size++;
	} while (value != 0);

	return size;
}

static void _write_varint(int fd, int value) {
	uint8_t buffer[5];
	int i = 0;

	while (1) {
		uint8_t temp = value & SEGMENT_BITS;
		value >>= 7;

		if (value != 0) {
			temp |= CONTINUE_BIT;
		}

		buffer[i++] = temp;

		if (value == 0) {
			break;
		}
	}

	send(fd, buffer, i, 0);
}

cmc_packet *cmc_parse_packet(cmc_config *config, int client_fd, void *buf, ssize_t len) {
	if (!buf || !len) {
		return NULL;
	}

	cmc_packet *packet = malloc(sizeof(cmc_packet));
	if (!packet) {
		return NULL;
	}
	memset(packet, 0, sizeof(cmc_packet));
	packet->client_fd = client_fd;

	DEBUG_HEX(buf, len);

	// Parse length
	const uint8_t *p = buf;
	packet->length = _read_varint(&p);
	CMC_DEBUG("Packet length: %d", packet->length);

	// Parse packet id
	packet->id = _read_varint(&p);
	CMC_DEBUG("Packet id: %d", packet->id);

	switch (packet->id) {
		case 0x00: {
			// Handshake or Login
			CMC_DEBUG("=> Handshake");
			packet->handshake = cmc_parse_handshake_packet(p, packet->length);

			if (!packet->handshake) {
				return NULL;
			}

			// Check intent
			switch (packet->handshake->intent) {
				case STATUS: {
					cmc_send_status_response(packet, config);
					break;
				}
				default: {
					break;
				}
			}

			break;
		}
		case 0x01: {
			// Ping
			CMC_DEBUG("=> Ping");
			cmc_send_ping_response(packet, p);

			break;
		}
	}

	return packet;
}

cmc_handshake_packet *cmc_parse_handshake_packet(const uint8_t *p, ssize_t len) {
	if (len == 1) {
		// Status Request packet
		CMC_DEBUG("=> Status Request");
		return NULL;
	}

	cmc_handshake_packet *packet = malloc(sizeof(cmc_handshake_packet));
	if (!packet) {
		return NULL;
	}
	memset(packet, 0, sizeof(cmc_handshake_packet));

	// Protocol version
	packet->protocol_version = _read_varint(&p);

	// Server address
	uint chars = *p++;
	for (int i = 0; i < chars; ++i) {
		packet->server_address[i] = p[0];
		p++;
	}
	packet->server_address[chars] = '\0';

	// Server port
	packet->server_port = p[0] << 8 | p[1];
	p += 2;

	// Intent
	uint8_t intent = *p;
	switch (intent) {
		case 1: {
			packet->intent = STATUS;
			break;
		}
		case 2: {
			packet->intent = LOGIN;
			break;
		}
		case 3: {
			packet->intent = TRANSFER;
			break;
		}
	}

	return packet;
}

void cmc_send_status_response(cmc_packet *packet, cmc_config *config) {
	cmc_status status = {
		.description = config->description,
		.max_players = config->max_players,
		.online_players = 0,
		.name = "1.21.8",
		.protocol = packet->handshake->protocol_version,
	};
	char *dump = cmc_json_build_status(&status);

	size_t json_len = strlen(dump);
	size_t packet_len = _varint_size(json_len) + 1 + json_len;

	_write_varint(packet->client_fd, packet_len);
	_write_varint(packet->client_fd, 0x00);
	_write_varint(packet->client_fd, json_len);
	send(packet->client_fd, dump, json_len, 0);

	free(dump);
}

void cmc_send_ping_response(cmc_packet *packet, const uint8_t *p) {
	if (!packet) {
		return;
	}
	int client_fd = packet->client_fd;

	uint8_t payload[8];
	memcpy(payload, p, 8);

	uint8_t out[10];
	out[0] = 0x09;
	out[1] = 0x01;
	memcpy(out + 2, payload, sizeof(payload));

	send(client_fd, out, sizeof(out), 0);
}

void cmc_free_packet(cmc_packet *packet) {
	if (!packet) {
		return;
	}

	if (packet->handshake) {
		free(packet->handshake);
	}

	free(packet);
}
