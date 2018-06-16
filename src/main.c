#include <stdio.h>
#include <config/cmd_options.h>

int main(int argc, const char **argv) {
    cmd_options_t opts = parse_options(argc, argv);
    if ((opts.run_type & RUN_TYPE_CMD_ERROR) == RUN_TYPE_CMD_ERROR) {
        fprintf(stderr, "Error while parsing option '%s'\n", opts.invalid_option);
        print_help(stderr, *argv);
    } else if (opts.run_type & RUN_TYPE_HELP) {
        print_help(stdout, *argv);
    } else if (opts.run_type & RUN_TYPE_VERSION) {
        print_version(stdout);
    }
    return 0;
}
