#ifndef CMC_PACKETS_H
#define CMC_PACKETS_H

#include <stdint.h>
#include <sys/types.h>

#define SERVER_ADDRESS_SIZE 255
#define SEGMENT_BITS 0x7F
#define CONTINUE_BIT 0x80

typedef struct cmc_handshake_packet_t {
	uint64_t protocol_version;
	char server_address[SERVER_ADDRESS_SIZE];
	unsigned short server_port;
	uint8_t intent;
} cmc_handshake_packet;

typedef struct cmc_packet_t {
	uint8_t id;
	struct cmc_handshake_packet_t *handshake;
} cmc_packet;

cmc_packet *cmc_parse_packet(void *buf, ssize_t len);
cmc_handshake_packet *cmc_parse_handshake_packet(const uint8_t *buf, ssize_t len);

void cmc_free_packet(cmc_packet *packet);

#endif
