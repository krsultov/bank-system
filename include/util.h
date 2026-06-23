#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

void read_line(char *buf, size_t size);

/* reads a positive number with at most 2 decimals; 1 on success, 0 on bad input */
int read_amount(double *out);

#endif
