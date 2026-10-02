#ifndef CMC_CONFIG_H
#define CMC_CONFIG_H

#define HOST_LEN 64
#define PORT_LEN 6
#define MOTD_LEN 1024
#define FAVICON_LEN 256

typedef struct cmc_config {
	char host[HOST_LEN];
	char port[PORT_LEN];
	int max_players;
	char motd[MOTD_LEN];
	char favicon[FAVICON_LEN];
} cmc_config;

cmc_config *cmc_config_load();
void cmc_config_free(cmc_config *config);

#endif
