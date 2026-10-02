#ifndef CMC_JSON_H
#define CMC_JSON_H

#include <stdint.h>

typedef struct cmc_status {
	const char *name;
	uint64_t protocol;
	int max_players;
	int online_players;
	char *motd;
} cmc_status;

char *cmc_json_build_status(cmc_status *status);

#endif
