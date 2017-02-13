#include "hexdump.h"

void hexcat(const void *a, size_t al, size_t start)
{
	fhexcat(stderr, a, al, start);
}

void hexcmp(const void *a, size_t al, const void *b, size_t bl)
{
	fhexcmp(stderr, a, al, b, bl);
}

#define hexout(...) fprintf(f, __VA_ARGS__)

void fhexcat(FILE *f, const void *a, size_t al, size_t start)
{
	const size_t cols = 16;
	const unsigned char *x = (const unsigned char *) a;
	size_t i = 0;
	while (i < al) {
		hexout("[%08zx]", i + start);
		for (size_t c = 0; c < cols; c++) {
			const size_t j = i + c;
			if (!(j & 3)) {
				hexout(" ");
			}
			if (j < al) {
				hexout(" %02hhx", x[c]);
			} else {
				hexout(" --");
			}
		}
		hexout("  ");
		for (size_t c = 0; c < cols; c++) {
			const size_t j = i + c;
			if (!(j & 3)) {
				hexout(" ");
			}
			if (j < al) {
				if (x[c] >= 32 && x[c] < 128) {
					hexout("%c", x[c]);
				} else {
					hexout(".");
				}
			} else {
				hexout(" ");
			}
		}
		hexout("\n");
		x += cols;
		i += cols;
	}
}

void fhexcmp(FILE *f, const void *a, size_t al, const void *b, size_t bl)
{
	const size_t cols = 8;
	const char *x = (const char *) a;
	const char *y = (const char *) b;
	size_t i = 0;
	while (i < al || i < bl) {
		hexout("[%08zx]", i);
		for (size_t c = 0; c < cols; c++) {
			const size_t j = i + c;
			if (!(j & 3)) {
				hexout(" ");
			}
			if (j < al) {
				hexout(" %02hhx", x[c]);
			} else {
				hexout(" --");
			}
		}
		{
			size_t ae = i + cols < al ? cols : al - i;
			size_t be = i + cols < bl ? cols : bl - i;
			if (ae != be || memcmp(x, y, cols) != 0) {
				hexout("  ┼");
			} else {
				hexout("  │");
			}
		}
		for (size_t c = 0; c < cols; c++) {
			const size_t j = i + c;
			if (!(j & 3)) {
				hexout(" ");
			}
			if (j < bl) {
				hexout(" %02hhx", y[c]);
			} else {
				hexout(" --");
			}
		}
		hexout("\n");
		x += cols;
		y += cols;
		i += cols;
	}
}
