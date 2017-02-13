#pragma once
#include <cstd/std.h>

void hexcat(const void *a, size_t al, size_t start);
void hexcmp(const void *a, size_t al, const void *b, size_t bl);

void fhexcat(FILE *f, const void *a, size_t al, size_t start);
void fhexcmp(FILE *f, const void *a, size_t al, const void *b, size_t bl);
