#ifndef CMC_DEBUG_H
#define CMC_DEBUG_H

#define CMC_DEBUG(msg, ...) fprintf(stdout, "[%s:%d] " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif
