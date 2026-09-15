#include <stdio.h>

#include "server.h"

int main(void) {
	fprintf(stdout, "Running cmc...\n");

	int sockfd = cmc_setup_socket();
	if (sockfd < 0) {
		fprintf(stderr, "cmc_setup_socket()\n");
		return -1;
	}

	cmc_server_loop(sockfd);

	return 0;
}
