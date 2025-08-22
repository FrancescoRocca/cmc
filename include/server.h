#ifndef CMC_SERVER_H
#define CMC_SERVER_H

#define EP_MAX_EVENTS 50
#define CMC_HOST "localhost"
#define CMC_PORT "25565"

int cmc_setup_socket();
void cmc_server_loop(int sockfd);
void cmc_handle_new_client(int sockfd, int epfd);
void cmc_handle_client_data(int client_fd, int epfd);

#endif
