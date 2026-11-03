#ifndef CMC_PACKET_H
#define CMC_PACKET_H

#include <stdint.h>
#include <sys/types.h>

#include "config.h"

#define CMC_SERVER_ADDR_SIZE 255
#define CMC_SEGMENT_BITS 0x7F
#define CMC_CONTINUE_BIT 0x80

typedef enum cmc_handshake_intent {
	CMC_STATUS,
	CMC_LOGIN,
	CMC_TRANSFER,
} cmc_handshake_intent;

typedef struct cmc_handshake_packet {
	uint64_t protocol_version;
	char server_address[CMC_SERVER_ADDR_SIZE];
	unsigned short server_port;
	cmc_handshake_intent intent;
} cmc_handshake_packet;

typedef struct cmc_packet {
	int client_fd;
	uint length;
	uint8_t id;
	cmc_handshake_packet *handshake;
} cmc_packet;

cmc_packet *cmc_parse_packet(int client_fd, void *buf, ssize_t len);
cmc_handshake_packet *cmc_parse_handshake_packet(const uint8_t *buf, ssize_t len);

void cmc_send_status_response(cmc_packet *packet, cmc_config *config);
void cmc_send_ping_response(cmc_packet *packet, const uint8_t *p);

void cmc_free_packet(cmc_packet *packet);

#endif
