#include "config.h"

#include <stdlib.h>
#include <string.h>
#include <tomlc17.h>

static int parse_string(toml_result_t *result, const char *str, void *dst, size_t dst_len) {
	toml_datum_t data = toml_seek(result->toptab, str);
	if (data.type != TOML_STRING) {
		return -1;
	}

	size_t chars = snprintf(dst, dst_len, "%s", data.u.s);
	if (chars >= dst_len) {
		return -1;
	}

	return 0;
}

static int parse_int(toml_result_t *result, const char *str, int *dst) {
	toml_datum_t data = toml_seek(result->toptab, str);
	if (data.type != TOML_INT64) {
		return -1;
	}

	*dst = data.u.int64;

	return 0;
}

cmc_error cmc_config_load(cmc_config *config) {
	if (!config) {
		return CMC_NULL;
	}

	cmc_error err = CMC_OK;

	// Parse toml file
	toml_result_t result = toml_parse_file_ex("server.toml");
	if (!result.ok) {
		return CONFIG_PARSE;
	}

	// Parse host
	if (parse_string(&result, "server.host", config->host, sizeof(config->host)) != 0) {
		err = CONFIG_HOST;
		goto error;
	}

	// Parse port
	if (parse_string(&result, "server.port", config->port, sizeof(config->port)) != 0) {
		err = CONFIG_PORT;
		goto error;
	}

	// Parse motd
	if (parse_string(&result, "server.motd", config->motd, sizeof(config->motd)) != 0) {
		err = CONFIG_MOTD;
		goto error;
	}

	// Parse max-players
	if (parse_int(&result, "server.max-players", &config->max_players) != 0) {
		err = CONFIG_MAX_PLAYERS;
		goto error;
	}

	// Parse favicon
	if (parse_string(&result, "server.favicon", config->favicon, sizeof(config->favicon)) != 0) {
		err = CONFIG_FAVICON;
		goto error;
	}

error:
	toml_free(result);
	return err;
}
