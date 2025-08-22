#include "packets.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* All data sent over the network (except for VarInt and VarLong) is big-endian */
static int _endianness() {
	int32_t one = 1;
	int8_t *p = (int8_t *)&one;

	/* Big Endian */
	int endianness = 1;

	if (p[0] == 1) {
		/* Little Endian */
		endianness = 0;
	}

	fprintf(stdout, "Endianness: %d\n", endianness);

	return endianness;
}

static void _print_hex(void *buf, ssize_t len) {
	fprintf(stdout, "[debug] len: %ld\n", len);
	const uint8_t *p = buf;
	for (ssize_t i = 0; i < len; ++i) {
		fprintf(stdout, "0x%02x ", p[i]);
	}
	fprintf(stdout, "\n");
	fflush(stdout);
}

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

cmc_packet *cmc_parse_packet(void *buf, ssize_t len) {
	if (!buf || !len) {
		return NULL;
	}

	cmc_packet *packet = malloc(sizeof(cmc_packet));
	if (!packet) {
		return NULL;
	}
	memset(packet, 0, sizeof(cmc_packet));

	//_endianness();
	_print_hex(buf, len);

	/* Parse length */
	const uint8_t *p = buf;
	uint length = p[0];
	p++;
	fprintf(stdout, "[debug] packet length: %d\n", length);

	packet->id = p[0];
	p++;
	fprintf(stdout, "[debug] packet id: %d\n", packet->id);
	if (packet->id == 0x00) {
		/* Handshake */
		fprintf(stdout, "[debug] Handshake\n");
		packet->handshake = cmc_parse_handshake_packet(p, length);
		if (!packet->handshake) {
			return NULL;
		}
	}

	return packet;
}

cmc_handshake_packet *cmc_parse_handshake_packet(const uint8_t *p, ssize_t len) {
	cmc_handshake_packet *packet = malloc(sizeof(cmc_handshake_packet));
	if (!packet) {
		return NULL;
	}
	memset(packet, 0, sizeof(cmc_handshake_packet));

	/* Protocol version */
	packet->protocol_version = _read_varint(&p);
	fprintf(stdout, "Protocol version: %ld\n", packet->protocol_version);

	/* Server address */
	uint chars = p[0];
	p++;
	fprintf(stdout, "Server address len: %d\n", chars);
	for (int i = 0; i < chars; ++i) {
		packet->server_address[i] = p[0];
		p++;
	}
	packet->server_address[chars] = '\0';
	fprintf(stdout, "Packet server address: %s\n", packet->server_address);

	/* Server port (2 bytes) */
	packet->server_port = p[0] << 8 | p[1];
	p += 2;
	fprintf(stdout, "Packet server port: %d\n", packet->server_port);

	/* Intent */
	packet->intent = p[0];
	fprintf(stdout, "Packet intent: %d\n", packet->intent);

	return packet;
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
