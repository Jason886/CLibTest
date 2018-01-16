#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LOG_I(char *text) {
    fprintf(stdout, "\033[32m%s\033[0m\n", text);
}

void LOG_W(char *text) {
    fprintf(stdout, "\033[33m%s\033[0m\n", text);
}

void LOG_E(char *text) {
    fprintf(stderr, "\033[31m%s\033[0m\n", text);
}

void LOG(char *text) {
    fprintf(stdout, "%s\n", text);
}
