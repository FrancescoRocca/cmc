#include "debug.h"

#include <stdint.h>
#include <stdio.h>

void DEBUG_HEX(void *buf, ssize_t len) {
	const uint8_t *p = buf;
	for (ssize_t i = 0; i < len; ++i) {
		fprintf(stdout, "0x%02x ", p[i]);
	}
	fprintf(stdout, "\n");
	fflush(stdout);
}
