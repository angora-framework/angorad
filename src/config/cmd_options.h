#ifndef ANGORAD_CONFIG_CMD_OPTIONS_H
#define ANGORAD_CONFIG_CMD_OPTIONS_H

#include <stdio.h>

#define RUN_TYPE_NORMAL 0
#define RUN_TYPE_HELP 1
#define RUN_TYPE_VERSION 2
#define RUN_TYPE_CMD_ERROR 5
#define RUN_TYPE_EXCLUSIVES 7
#define RUN_TYPE_FOREGROUND 8

typedef struct {
    int run_type;
    const char *invalid_option;
    const char *config_file;
} cmd_options_t;

cmd_options_t parse_options(int argc, const char **argv);

void print_help(FILE *f, const char *argv0);

void print_version(FILE *f);

#endif
