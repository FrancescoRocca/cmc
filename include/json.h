#ifndef CMC_JSON_H
#define CMC_JSON_H

#include <stdint.h>

char *cmc_json_build_status(const char *name, uint64_t protocol, int max_players, int online_players,
                            char *description_text);

#endif
