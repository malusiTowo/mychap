/*
** EPITECH PROJECT, 2018
** PARSING
** File description:
** PARSING
*/

#include "chap.h"
#include "global.h"

bool check_ip(const char *str)
{
    if (strcmp(str, "localhost") == 0)
        return true;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.')
            continue;
        if (!(str[i] >= '0' && str[i] <= '9'))
            return false;
    }

    return true;
}

bool check_port(const char *str)
{
    int port = atoi(str);
    return port > 1024 ? true : false;
}

bool evaluate_opt(int *opt, cmd_args *args)
{
    switch (*opt) {
        case 't':
            args->ip = check_ip(optarg) ? strdup(optarg) : NULL;
            if (!args->ip)
                return false;
            break;
        case 'p':
            args->port = check_port(optarg) ? strdup(optarg) : NULL;
            if (!args->port)
                return false;
            break;
        case 'P':
            args->password = strdup(optarg);
            break;
        case ':':
        case '?':
            return false;
    }
    return true;
}

bool parse_cmd_args(int ac, char **av, cmd_args *args)
{
    int opt;
    static struct option long_options[] =
    {
        {"password", required_argument, NULL, 'P'},
        {"port", required_argument, NULL, 'p'},
        {"target", required_argument, NULL, 't'},
        {NULL, 0, NULL, 0}
    };

    while ((opt = getopt_long(ac, av, ":t:p:P:",
    long_options, NULL)) != ERROR) {
        if (!evaluate_opt(&opt, args))
            return false;
    }
    if (optind < ac)
        return false;
    return true;
}