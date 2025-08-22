#include "server.h"

#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int cmc_setup_socket() {
	struct addrinfo hints;
	struct addrinfo *result;
	int ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;       /* IPv4 */
	hints.ai_socktype = SOCK_STREAM; /* TCP */
	hints.ai_flags = AI_PASSIVE;

	ret = getaddrinfo(CMC_HOST, CMC_PORT, &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(ret));
		return -1;
	}

	int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sockfd == -1) {
		fprintf(stderr, "socket()\n");
		return -1;
	}

	ret = bind(sockfd, result->ai_addr, result->ai_addrlen);
	if (ret != 0) {
		fprintf(stderr, "bind()\n");
		close(sockfd);
		return -1;
	}

	ret = listen(sockfd, 20);
	if (ret != 0) {
		fprintf(stderr, "listen()\n");
		close(sockfd);
		return -1;
	}

	return sockfd;
}

void cmc_server_loop(int sockfd) {
	struct sockaddr_storage peer_addr;
	socklen_t peer_len = sizeof(peer_addr);
	int client_fd;

	for (;;) {
		/* Accept a new client */
		client_fd = accept(sockfd, (struct sockaddr *)&peer_addr, &peer_len);
		if (client_fd == -1) {
			fprintf(stderr, "accept()\n");
			continue;
		}

		char buf[4096];
		/* Read data from client */
		ssize_t bytes = recv(client_fd, buf, sizeof(buf) - 1, 0);
		buf[bytes] = '\0';
		fprintf(stdout, "Received from client: %s\n", buf);
		char answer[32] = "Bye!";
		send(client_fd, answer, sizeof(answer), 0);

		close(client_fd);
	}
}

/* All data sent over the network (except for VarInt and VarLong) is big-endian */
int _endianness() {
	int32_t one = 1;
	int8_t *p = (int8_t *)&one;

	if (p[0] == 1) {
		/* Little endian */
		return 0;
	} else {
		/* Big endian */
		return 1;
	}
}
