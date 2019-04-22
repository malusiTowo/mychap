/*
** EPITECH PROJECT, 2018
** UTILS
** File description:
** UTILS
*/

#include "global.h"
#include "chap.h"

void usage(int code)
{
    printf("USAGE: /client -t localhost -p 4241 -P \"password\"\n");
    exit(code);
}

// FIXME: parse cmd args correctly
void error_handling(int ac, char **av)
{
    if (ac != 7)
        usage(FAIL);
}

void cleanup(client *client, cmd_args *args)
{
    free(args->port);
    free(args->ip);
    free(args->password);
    free(client->_config);
    close(client->sock);
}