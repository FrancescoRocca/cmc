#include "error.h"

#include <stddef.h>

#define ARR_SIZE(X) (sizeof(X) / sizeof(*X))

static err errors[] = {
	{CMC_OK, "No error"},
	{CMC_ERR, "Something happened"},
	{CMC_NULL, "Null value passed"},
	{CMC_CONFIG_PARSE, "Config file invalid or missing"},
	{CMC_CONFIG_HOST, "Missing or invalid server host"},
	{CMC_CONFIG_PORT, "Missing or invalid server port"},
	{CMC_CONFIG_VERSION, "Missing or invalid server version"},
	{CMC_CONFIG_MAX_PLAYERS, "Missing or invalid server max players"},
	{CMC_CONFIG_MOTD, "Missing or invalid server motd"},
	{CMC_CONFIG_FAVICON, "Missing or invalid server favicon"},
};

char *cmc_error_get(cmc_error err) {
	for (size_t i = 0; i < ARR_SIZE(errors); ++i) {
		if (err == errors->error) {
			return errors->msg;
		}
	}

	return "Cannot find this error?!";
}
