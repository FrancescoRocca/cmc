#include "json.h"

#include <jansson.h>

char *cmc_json_build_status(const char *name, uint64_t protocol, int max_players, int online_players,
							char *description_text) {
	json_t *root = json_object();

	json_t *version = json_object();
	json_object_set_new(version, "name", json_string(name));
	json_object_set_new(version, "protocol", json_integer(protocol));
	json_object_set_new(root, "version", version);

	json_t *players = json_object();
	json_object_set_new(players, "max", json_integer(max_players));
	json_object_set_new(players, "online", json_integer(online_players));
	json_object_set_new(root, "players", players);

	json_t *sample = json_array();
	json_t *ptest = json_object();
	json_object_set_new(ptest, "name", json_string("I'm coded in C!"));
	json_object_set_new(ptest, "id", json_string("0541ed27-7595-4e6a-9101-6c07f879b7b5"));
	json_array_append_new(sample, ptest);
	json_object_set_new(players, "sample", sample);

	json_t *description = json_object();
	json_object_set_new(description, "text", json_string(description_text));
	json_object_set_new(root, "description", description);

	/* TODO: use a config instead of hardcoding the favicon */
	char favicon[4096] =
		"data:image/"
		"png;base64,"
		"iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAACdeAAAnXgHPwViOAAAAGXRFWHRTb2Z0d2FyZQB3d3cuaW5rc2NhcG"
		"Uub3Jnm+48GgAAA1dJREFUeJztm8FPE0EUxr+"
		"3u6BE8KAJQZCbisbEgsSEpi0pqEeDF4hcTEy8Ef8EEv4Iw8UYTfSANpGEK1EaaEOM0UIjMcBNCKKJB4VTy87zQFta0t1u2WUH2/"
		"mdtvte3nzvy3Q6u9sFFPUNWQV6I5ELpjB6QHTGT0FeQ4xdo0GkPsXj22Xjh08EgoMdZGASjHvl4v8pAsAMsT6WSs5uFQdKGgwEBzs0nRcZ1Omr"
		"PJ8g8AbY6Cs2QStJMDBZq80DAIM6mcynxecKM6AndLedydxE7Ux7K0SDITrya0LRDDADqP3mAUDLmBQofMgfMKFZjh7/"
		"Iaaz+WPNLrEeUAbIFiAbZYBsAbJRBsgWIBvDbQFienyp/dzLWCxmWuVcj0abG7L6axAPOSw7nTXEw5V4fNcqYXh4WF/f/"
		"v0IjGdViy7C9Qyo1DwArMTju6RhymlNZnpj1zwAxGIx83Lb+RdOa1rh2oBKzedhZkd5AEDEwsux7aj7NUAZIFuAbJQBsgXIRhngtkBXKNTiJI/"
		"BjvL2c53dnHE6th2ud4JNOP2qJ3J7yu53nsEtxDQOoiWA1yuUvELg8UB4gAi0Y5VERDqDR8FHlg7AAwNAPMQM2y0ugQDC8lIi0gtMVNjkTGjd4"
		"fkvBDy3y2J22XkOP9eAtcrNA7mctWNXk0MtgrIFyKbuDXC/"
		"CB7wSzD3p5Nzq24LLSU+jFjFboQGujSieQCtbscBPJwBBCS8aL4S6eTcKgEJr+p5ZgADrq/"
		"NZYxV92uAMkC2ANkoA2QLkI0yQLYA2Xi5E7TlRjR6UdvTgk5yhSEW0/"
		"H45nFrAnw0INf8W4e5IwBix6soN5Yfg5xklAFeFSJAt40T2caLYSZbXZXGqgYvL4bCvcHo1XKxrlCohcGjTmsR8QOrO743++"
		"9cYyByVJ2H8XIRbDV17Vt3eLB8tLp7mPeb6NTfcrWEcPTg2DFqDZAtQDbKANkCZKMMkC1ANsqAgwPrJ7G1Bgv8yR8XDCDKLGP/"
		"7apaRzQ2inT+Q8GAzwsLPwDMSJHkI8w0XfwOYelbY6yPEXjDf1m+8d3QMk+"
		"KT5QYkErOboGNPgDTqK2vgyDgnU7ZvtxML2D5ltitaLTN3NO7RRX/7TmJaKCdTBaprx/f/5StRXES+Qfq2fZ/"
		"nG9J9gAAAABJRU5ErkJggg==";

	json_object_set_new(root, "favicon", json_string(favicon));
	json_object_set(root, "enforcesSecureChat", json_boolean(0));

	char *dump = json_dumps(root, JSON_INDENT(4));

	json_decref(root);

	return dump;
}
