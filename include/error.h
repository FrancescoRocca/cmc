#ifndef CMC_ERROR_H
#define CMC_ERROR_H

typedef enum cmc_error {
	CMC_OK,
	CMC_ERR,
	CMC_NULL,
	CONFIG_PARSE,
	CONFIG_HOST,
	CONFIG_PORT,
	CONFIG_MAX_PLAYERS,
	CONFIG_MOTD,
	CONFIG_FAVICON,
} cmc_error;

typedef struct err {
	cmc_error error;
	char *msg;
} err;

char *cmc_error_get(cmc_error err);

#endif
