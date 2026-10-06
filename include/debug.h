#ifndef CMC_DEBUG_H
#define CMC_DEBUG_H

#include <sys/types.h>

#define CMC_DEBUG(msg, ...) fprintf(stdout, "[%s:%d] " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)

void DEBUG_HEX(void *buf, ssize_t len);

#endif
