#ifndef CMC_PACKET_H
#define CMC_PACKET_H

#include <stdint.h>
#include <sys/types.h>

#include "config.h"

#define SERVER_ADDRESS_SIZE 255
#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

/* Packet Format */
/* Length - VarInt (PacketID + Data) */
/* Packet ID - VarInt */
/* Data - ByteArray */

typedef enum cmc_handshake_intent {
	STATUS,
	LOGIN,
	TRANSFER,
} cmc_handshake_intent;

typedef struct cmc_handshake_packet {
	uint64_t protocol_version;
	char server_address[SERVER_ADDRESS_SIZE];
	unsigned short server_port;
	cmc_handshake_intent intent;
} cmc_handshake_packet;

typedef struct cmc_packet {
	int client_fd;
	uint length;
	uint8_t id;
	cmc_handshake_packet *handshake;
} cmc_packet;

cmc_packet *cmc_parse_packet(cmc_config *config, int client_fd, void *buf, ssize_t len);
cmc_handshake_packet *cmc_parse_handshake_packet(const uint8_t *buf, ssize_t len);

void cmc_send_status_response(cmc_packet *packet, cmc_config *config);
void cmc_send_ping_response(cmc_packet *packet, const uint8_t *p);

void cmc_free_packet(cmc_packet *packet);

#endif
