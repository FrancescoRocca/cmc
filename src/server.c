#include "server.h"

#include <errno.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "debug.h"
#include "packet.h"

int cmc_setup_socket() {
	struct addrinfo hints;
	struct addrinfo *result;
	int ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	ret = getaddrinfo(CMC_HOST, CMC_PORT, &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(ret));
		return -1;
	}

	int sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sockfd == -1) {
		fprintf(stderr, "socket(): %s\n", strerror(errno));
		return -1;
	}

	ret = bind(sockfd, result->ai_addr, result->ai_addrlen);
	if (ret != 0) {
		fprintf(stderr, "bind(): %s\n", strerror(errno));
		close(sockfd);
		return -1;
	}

	ret = listen(sockfd, 20);
	if (ret != 0) {
		fprintf(stderr, "listen(): %s\n", strerror(errno));
		close(sockfd);
		return -1;
	}

	return sockfd;
}

static void cmc_epoll_add(int epfd, int fd) {
	struct epoll_event ev = {
		.data.fd = fd,
		.events = EPOLLIN,
	};

	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

static void cmc_epoll_del(int epfd, int fd) {
	struct epoll_event ev = {
		.data.fd = fd,
		.events = EPOLLIN,
	};

	epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
}

void cmc_server_loop(int sockfd) {
	int epfd = epoll_create1(0);
	cmc_epoll_add(epfd, sockfd);

	struct epoll_event events[EP_MAX_EVENTS];
	int nfds;

	for (;;) {
		/* Accept a new client */
		nfds = epoll_wait(epfd, events, EP_MAX_EVENTS, -1);

		if (nfds == 0) {
			continue;
		}

		for (int i = 0; i < nfds; ++i) {
			if (events[i].data.fd == sockfd) {
				/* Handle new connection */
				cmc_handle_new_client(sockfd, epfd);
			} else {
				/* Handle client data */
				cmc_handle_client_data(events[i].data.fd, epfd);
			}
		}
	}
}

void cmc_handle_new_client(int sockfd, int epfd) {
	struct sockaddr_storage peer_addr;
	socklen_t peer_len = sizeof(peer_addr);

	int client_fd = accept(sockfd, (struct sockaddr *)&peer_addr, &peer_len);
	if (client_fd == -1) {
		fprintf(stderr, "accept()\n");
	}

	cmc_epoll_add(epfd, client_fd);
}

void cmc_handle_client_data(int client_fd, int epfd) {
	uint8_t buf[4096];

	ssize_t bytes = recv(client_fd, buf, sizeof(buf) - 1, 0);
	CMC_DEBUG("Received %ld bytes", bytes);
	if (bytes == 0) {
		CMC_DEBUG("Client disconnected");
		close(client_fd);
		cmc_epoll_del(epfd, client_fd);
		return;
	}

	cmc_packet *packet = cmc_parse_packet(client_fd, buf, bytes);

	cmc_free_packet(packet);
}
