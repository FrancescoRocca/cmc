#ifndef CMC_CONFIG_H
#define CMC_CONFIG_H

#include "error.h"

#define CMC_HOST_LEN 64
#define CMC_PORT_LEN 6
#define CMC_VERSION_LEN 32
#define CMC_MOTD_LEN 1024
#define CMC_FAVICON_LEN 256

typedef struct cmc_config {
	char host[CMC_HOST_LEN];
	char port[CMC_PORT_LEN];
	char version[CMC_VERSION_LEN];
	int max_players;
	char description[CMC_MOTD_LEN];
	char favicon[CMC_FAVICON_LEN];
} cmc_config;

cmc_error cmc_config_load(cmc_config *config);

#endif
