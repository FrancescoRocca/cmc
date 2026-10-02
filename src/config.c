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

cmc_config *cmc_config_load() {
	// Parse toml file
	toml_result_t result = toml_parse_file_ex("server.toml");
	if (!result.ok) {
		return NULL;
	}

	// Allocate config struct
	cmc_config *config = malloc(sizeof(*config));
	if (!config) {
		return NULL;
	}

	// Parse host
	if (parse_string(&result, "server.host", config->host, sizeof(config->host)) != 0) {
		fprintf(stderr, "Missing or invalid sever.host in config\n");
		goto error;
	}

	// Parse port
	if (parse_string(&result, "server.port", config->port, sizeof(config->port)) != 0) {
		fprintf(stderr, "Missing or invalid server.port in config\n");
		goto error;
	}

	// Parse motd
	if (parse_string(&result, "server.motd", config->motd, sizeof(config->motd)) != 0) {
		fprintf(stderr, "Missing or invalid server.motd in config\n");
		goto error;
	}

	// Parse max-players
	if (parse_int(&result, "server.max-players", &config->max_players) != 0) {
		fprintf(stderr, "Missing or invalid server.max-players in config\n");
		goto error;
	}

	toml_free(result);
	return config;

error:
	cmc_config_free(config);
	toml_free(result);
	return NULL;
}

void cmc_config_free(cmc_config *config) {
	if (config) {
		free(config);
	}
}
