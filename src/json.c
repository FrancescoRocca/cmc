#include "json.h"

#include <yyjson.h>

char *cmc_json_build_status(cmc_status *status) {
	// Make a new json document
	yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
	yyjson_mut_val *root = yyjson_mut_obj(doc);
	yyjson_mut_doc_set_root(doc, root);

	// Add version and protocol
	yyjson_mut_val *version = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, version, "name", status->name);
	yyjson_mut_obj_add_uint(doc, version, "protocol", status->protocol);
	yyjson_mut_obj_add_val(doc, root, "version", version);

	// Add players count
	yyjson_mut_val *players = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_int(doc, players, "max", status->max_players);
	yyjson_mut_obj_add_int(doc, players, "online", status->online_players);
	yyjson_mut_obj_add_val(doc, root, "players", players);

	// Players list
	yyjson_mut_val *sample = yyjson_mut_arr(doc);
	yyjson_mut_val *ptest = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, ptest, "name", "I'm coded in C!");
	yyjson_mut_obj_add_str(doc, ptest, "id", "0541ed27-7595-4e6a-9101-6c07f879b7b5");
	yyjson_mut_arr_add_val(sample, ptest);
	yyjson_mut_obj_add_val(doc, players, "sample", sample);

	// Motd
	yyjson_mut_val *desc = yyjson_mut_obj(doc);
	yyjson_mut_obj_add_str(doc, desc, "text", status->motd);
	yyjson_mut_obj_add_val(doc, root, "description", desc);

	// Add favicon
	yyjson_mut_obj_add_str(doc, root, "favicon", status->favicon);
	yyjson_mut_obj_add_bool(doc, root, "enforcesSecureChat", false);

	char *dump = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);

	yyjson_mut_doc_free(doc);

	return dump;
}
