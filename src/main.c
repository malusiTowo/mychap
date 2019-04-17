/*
** EPITECH PROJECT, 2018
** MAIN
** File description:
** MAIN
*/

#include "chap.h"
#include "global.h"

void create_socket(client *client)
{
    if ((client->sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == ERROR) {
        perror("socket");
        exit(FAIL);
    }
}

void configure_socket(client *client, struct sockaddr_in *config, int port)
{
    int opt = 1;
    config->sin_family = AF_INET;
    config->sin_addr.s_addr = htonl(INADDR_ANY);
    config->sin_port = htons(port);

    if (setsockopt(client->sock, SOL_SOCKET, IP_HDRINCL,
    &opt, sizeof(opt)) < SUCCESS) {
        perror("setsockopt");
        exit(FAIL);
    }
}

void bind_socket(client *client, struct sockaddr_in *config)
{
    if ((bind(client->sock, (struct sockaddr *)config,
    sizeof(config))) == ERROR) {
        perror("bind failed");
        exit(FAIL);
    }
}

void init_client(client *client, cmd_args *args)
{
    struct sockaddr_in config;

    if (!client) {
        if ((client = malloc(sizeof(client))) == NULL) {
            perror("malloc");
            exit(FAIL);
        }
        create_socket(client);
        configure_socket(client, &config, atoi(args->port));
        bind_socket(client, &config);
    }
}

void usage(int code)
{
    printf("USAGE: /client -t localhost -p 4241 -P \"password\"\n");
    exit(code);
}

bool check_numeric(const char *str, bool isIp)
{
    if (isIp && strcmp(str, "localhost") == 0)
        return true;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isIp && str[i] == '.')
            continue;
        if (str[i] < '0' && str[i] > '9')
            return false;
    }
    return true;
}

bool evaluate_opt(int *opt, cmd_args *args)
{
    switch (*opt) {
        case 'h':
            usage(SUCCESS);
        case 't':
            args->ip =
            check_numeric(optarg, true) ? strdup(optarg) : NULL;
            break;
        case 'p':
            args->port =
            check_numeric(optarg, false) ? strdup(optarg) : NULL;
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

void parse_cmd_args(int ac, char **av, cmd_args *args)
{
    int opt;
    int error = 0;

    if (ac != 7)
        usage(FAIL);
    while((opt = getopt(ac, av, ":t:p:P:")) != ERROR) {
        if (!evaluate_opt(&opt, args))
            error = 1;
    }
    // TODO: check if all attributes are correctly added
    if (optind < ac || error != 0)
        usage(FAIL);
}

int main(int ac, char *av[])
{
    client *client = NULL;
    int port = 0;
    cmd_args args;

    parse_cmd_args(ac, av, &args);
    init_client(client, &args);
    // create headers
    // send message to server
    return 0;
}