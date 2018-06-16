#include <stdio.h>
#include <string.h>
#include <config/cmd_options.h>
#include <config.h>

/*
 * # function name, flags, parameters, description
 * options = [
 *     ("help", [ "-h", "--help" ], [], r'"Shows this help message and exits"'),
 *     ("version", [ "-v", "--version" ], [], r'"Shows the version of the program and exits"'),
 *     ("foreground", [ "-f", "--foreground" ], [], r'"Runs the process in the foreground instead of detaching and running in the background"'),
 *     ("configfile", [ "-c", "--config" ], [ "config.conf" ], r'"Uses the following argument as a configuration file [default: " SYSCONF_DIR "/" PACKAGE "/" PACKAGE ".conf]"')
 * ]
 * 
 * for option in options:
 *     print("inline void process_option_%s(const char ***argi, const char **argf, cmd_options_t *options);" % option[0])
 */
inline void process_option_invalid(const char ***argi, const char **argf, cmd_options_t *options);

cmd_options_t parse_options(int argc, const char **argv) {
    cmd_options_t options = {
        .run_type = RUN_TYPE_NORMAL,
        .invalid_option = NULL,
        .config_file = ""
    };
    const char **argf = argv + argc;
    for (const char **argi = argv + 1; argi != argf; ++argi) {
        int diff;
        /*
         * map = []
         * for option in options:
         *     for flag in option[1]:
         *         map.append((flag, option[0]))
         * map.sort(key = lambda t: t[0])
         * 
         * def binary_search(start, end):
         *     mid = start + (end - start) // 2
         *     print(r'diff = strcmp(*argi, "%s");' % map[mid][0])
         *     if start >= end:
         *         print(r'if (diff == 0) {')
         *         print(r'    process_option_%s(&argi, argf, &options);' % map[mid][1])
         *         print(r'} else {')
         *         print(r'    process_option_invalid(&argi, argf, &options);')
         *         print(r'}')
         *     else:
         *         print(r'if (diff < 0) {')
         *         binary_search(start, mid - 1)
         *         print(r'} else if (diff > 0) {')
         *         binary_search(mid + 1, end)
         *         print(r'} else if (diff == 0) {')
         *         print(r'    process_option_%s(&argi, argf, &options);' % map[mid][1])
         *         print(r'}')
         * 
         * binary_search(0, len(map) - 1)
         */
    }
    return options;
}

void print_help(FILE *f, const char *argv0) {
    fputs("Usage:\n", f);
    fprintf(f, "%s"
        /*
         * for option in options:
         *     print(r'" [%s%s%s]"' % ("|".join(option[1]), "" if len(option[2]) == 0 else " ", " ".join(option[2])))
         */
        "\n",
        argv0
    );
    fputs("\n", f);
    fputs("Options:\n", f);
    /*
     * max_width = 0
     * for option in options:
     *     width = len("%s%s%s" % (", ".join(option[1]), "" if len(option[2]) == 0 else " ", " ".join(option[2])))
     *     if width > max_width:
     *         max_width = width
     * max_width += 5
     * for option in options:
     *     opt = "    %s%s%s" % (", ".join(option[1]), "" if len(option[2]) == 0 else " ", " ".join(option[2]))
     *     opt += " " * (max_width - len(opt))
     *     print(r'fputs("%s" %s "\n", f);' % (opt, option[3]))
     */
}

void print_version(FILE *f) {
    fputs(PACKAGE_STRING "\n", f);
    fputs("Email bug reports to <" PACKAGE_BUGREPORT ">.\n", f);
}

inline void process_option_help(const char ***argi, const char **argf, cmd_options_t *options) {
    if (options->run_type & RUN_TYPE_EXCLUSIVES) {
        if ((options->run_type & RUN_TYPE_CMD_ERROR) != RUN_TYPE_CMD_ERROR) {
            options->run_type |= RUN_TYPE_CMD_ERROR;
            options->invalid_option = **argi;
        }
    } else {
        options->run_type |= RUN_TYPE_HELP;
    }
}

inline void process_option_version(const char ***argi, const char **argf, cmd_options_t *options) {
    if (options->run_type & RUN_TYPE_EXCLUSIVES) {
        if ((options->run_type & RUN_TYPE_CMD_ERROR) != RUN_TYPE_CMD_ERROR) {
            options->run_type |= RUN_TYPE_CMD_ERROR;
            options->invalid_option = **argi;
        }
    } else {
        options->run_type |= RUN_TYPE_VERSION;
    }
}

inline void process_option_foreground(const char ***argi, const char **argf, cmd_options_t *options) {
    if (options->run_type & RUN_TYPE_FOREGROUND) {
        if ((options->run_type & RUN_TYPE_CMD_ERROR) != RUN_TYPE_CMD_ERROR) {
            options->run_type |= RUN_TYPE_CMD_ERROR;
            options->invalid_option = **argi;
        }
    } else {
        options->run_type |= RUN_TYPE_FOREGROUND;
    }
}

inline void process_option_configfile(const char ***argi, const char **argf, cmd_options_t *options) {
    if (options->config_file || *argi + 1 == argf) {
        if ((options->run_type & RUN_TYPE_CMD_ERROR) != RUN_TYPE_CMD_ERROR) {
            options->run_type |= RUN_TYPE_CMD_ERROR;
            options->invalid_option = **argi;
        }
    } else {
        options->config_file = *++*argi;
    }
}

inline void process_option_invalid(const char ***argi, const char **argf, cmd_options_t *options) {
    if ((options->run_type & RUN_TYPE_CMD_ERROR) != RUN_TYPE_CMD_ERROR) {
        options->run_type = RUN_TYPE_CMD_ERROR;
        options->invalid_option = **argi;
    }
}
