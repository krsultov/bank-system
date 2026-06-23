#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    size_t n = strlen(buf);
    if (n > 0 && buf[n - 1] == '\n') {
        buf[n - 1] = '\0';
    }
}

int read_amount(double *out) {
    char buf[64];
    read_line(buf, sizeof(buf));

    int digits = 0, decimals = 0, seenDot = 0;
    for (int i = 0; buf[i] != '\0'; i++) {
        char c = buf[i];
        if (c == '.') {
            if (seenDot) return 0;
            seenDot = 1;
        } else if (c >= '0' && c <= '9') {
            digits++;
            if (seenDot) decimals++;
        } else {
            return 0;
        }
    }

    if (digits == 0 || decimals > 2) return 0;

    double value = atof(buf);
    if (value <= 0.0) return 0;

    *out = value;
    return 1;
}
