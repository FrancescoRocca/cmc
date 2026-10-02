#include "json.h"

#include <yyjson.h>

char *cmc_json_build_status(cmc_status *status) {
	yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
	yyjson_mut_val *root = yyjson_mut_obj(doc);
	yyjson_mut_doc_set_root(doc, root);

	yyjson_mut_val *version = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, version, "name", status->name);
	yyjson_mut_obj_add_uint(doc, version, "protocol", status->protocol);
	yyjson_mut_obj_add_val(doc, root, "version", version);

	yyjson_mut_val *players = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_int(doc, players, "max", status->max_players);
	yyjson_mut_obj_add_int(doc, players, "online", status->online_players);
	yyjson_mut_obj_add_val(doc, root, "players", players);

	yyjson_mut_val *sample = yyjson_mut_arr(doc);
	yyjson_mut_val *ptest = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, ptest, "name", "I'm coded in C!");
	yyjson_mut_obj_add_str(doc, ptest, "id", "0541ed27-7595-4e6a-9101-6c07f879b7b5");
	yyjson_mut_arr_add_val(sample, ptest);
	yyjson_mut_obj_add_val(doc, players, "sample", sample);

	yyjson_mut_val *desc = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, desc, "text", status->motd);
	yyjson_mut_obj_add_val(doc, root, "description", desc);

	/* @TODO: use a config instead of hardcoding the favicon */
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

	yyjson_mut_obj_add_str(doc, root, "favicon", favicon);
	yyjson_mut_obj_add_bool(doc, root, "enforcesSecureChat", false);

	char *dump = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);

	yyjson_mut_doc_free(doc);

	return dump;
}
