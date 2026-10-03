#include "error.h"

#include <stddef.h>

#define ARR_SIZE(X) (sizeof(X) / sizeof(*X))

static err errors[] = {
	{CMC_OK, "No error"},
	{CMC_ERR, "Something happened"},
	{CMC_NULL, "Null value passed"},
	{CONFIG_PARSE, "Config file invalid or missing"},
	{CONFIG_HOST, "Missing or invalid server host"},
	{CONFIG_PORT, "Missing or invalid server port"},
	{CONFIG_MAX_PLAYERS, "Missing or invalid server max players"},
	{CONFIG_MOTD, "Missing or invalid server motd"},
	{CONFIG_FAVICON, "Missing or invalid server favicon"},
};

char *cmc_error_get(cmc_error err) {
	for (size_t i = 0; i < ARR_SIZE(errors); ++i) {
		if (err == errors->error) {
			return errors->msg;
		}
	}

	return "Cannot find this error?!";
}
