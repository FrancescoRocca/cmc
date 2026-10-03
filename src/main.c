#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "debug.h"
#include "server.h"

int main(void) {
	// Load server config from file
	cmc_error err;
	cmc_config config;

	err = cmc_config_load(&config);
	if (err != CMC_OK) {
		fprintf(stderr, "%s\n", cmc_error_get(err));
		exit(EXIT_FAILURE);
	}

	CMC_DEBUG("Running cmc (%s:%s)\n", config.host, config.port);
	CMC_DEBUG("MOTD: %s\n", config.motd);
	CMC_DEBUG("Max players: %d\n", config.max_players);

	// Setup server socket
	int sockfd = cmc_setup_socket(&config);
	if (sockfd < 0) {
		fprintf(stderr, "cmc_setup_socket()\n");
	}

	// Main server loop
	cmc_server_loop(&config, sockfd);

	return EXIT_SUCCESS;
}
