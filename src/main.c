#include <stdio.h>

#include "server.h"

int main(void) {
	int sockfd = cmc_setup_socket();
	if (sockfd < 0) {
		fprintf(stderr, "cmc_setup_socket()\n");
		return -1;
	}

	fprintf(stdout, "sockfd: %d\n", sockfd);
	int endian = _endianness();
	fprintf(stdout, "endian: %d\n", endian);

	cmc_server_loop(sockfd);

	return 0;
}
