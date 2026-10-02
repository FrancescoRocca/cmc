#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "server.h"

int main(void) {
	// Load server config from file
	cmc_config *config = cmc_config_load();
	if (!config) {
		fprintf(stderr, "Unable to load config file\n");
		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "Running cmc (%s:%s)\n", config->host, config->port);
	fprintf(stdout, "MOTD: %s\n", config->motd);
	fprintf(stdout, "Max players: %d\n", config->max_players);

	// Setup server socket
	int sockfd = cmc_setup_socket(config);
	if (sockfd < 0) {
		fprintf(stderr, "cmc_setup_socket()\n");
		goto cleanup;
	}

	cmc_server_loop(config, sockfd);

cleanup:
	cmc_config_free(config);

	return EXIT_SUCCESS;
}
