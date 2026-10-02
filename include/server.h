#ifndef CMC_SERVER_H
#define CMC_SERVER_H

#include "config.h"

#define EP_MAX_EVENTS 50

int cmc_setup_socket(cmc_config *config);
void cmc_server_loop(cmc_config *config, int sockfd);
void cmc_handle_new_client(int sockfd, int epfd);
void cmc_handle_client_data(cmc_config *config, int client_fd, int epfd);

#endif
