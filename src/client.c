#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define host "localhost"
#define port "25565"

int main(void) {
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	int ret = getaddrinfo(host, port, &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(ret));
		return -1;
	}

	int sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sock == -1) {
		fprintf(stderr, "socket()\n");
		return -1;
	}

	ret = connect(sock, result->ai_addr, result->ai_addrlen);
	if (ret != 0) {
		fprintf(stderr, "connect()\n");
		close(sock);
	}

	char msg[32] = "Hello cmc!";
	char buf[4096];
	send(sock, msg, sizeof(msg), 0);
	ssize_t bytes = recv(sock, buf, sizeof(buf), 0);
	buf[bytes] = '\0';
	fprintf(stdout, "Received: %s\n", buf);

	close(sock);

	return 0;
}
