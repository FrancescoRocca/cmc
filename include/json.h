#ifndef CMC_JSON_H
#define CMC_JSON_H

#include <stdint.h>

typedef struct cmc_status {
	const char *name;
	uint64_t protocol;
	int max_players;
	int online_players;
	char *description;
	char favicon[4092];
} cmc_status;

// Return the stringify json
char *cmc_json_build_status(cmc_status *status);

#endif
