#ifndef CMC_ERROR_H
#define CMC_ERROR_H

typedef enum cmc_error {
	CMC_OK,
	CMC_ERR,
	CMC_NULL,
	CMC_CONFIG_PARSE,
	CMC_CONFIG_HOST,
	CMC_CONFIG_PORT,
	CMC_CONFIG_VERSION,
	CMC_CONFIG_MAX_PLAYERS,
	CMC_CONFIG_MOTD,
	CMC_CONFIG_FAVICON,
} cmc_error;

typedef struct err {
	cmc_error error;
	char *msg;
} err;

char *cmc_error_get(cmc_error err);

#endif
