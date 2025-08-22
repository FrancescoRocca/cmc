#ifndef CMC_SERVER_H
#define CMC_SERVER_H

#define CMC_HOST "localhost"
#define CMC_PORT "25565"

int cmc_setup_socket();
void cmc_server_loop(int sockfd);

int _endianness();

#endif
