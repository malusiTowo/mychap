/*
** EPITECH PROJECT, 2018
** MAIN
** File description:
** MAIN
*/

#include "chap.h"
#include "global.h"

int main(int ac, char *av[])
{
    client client;
    int port = 0;
    cmd_args args;

    if (!error_handling(ac, av) || !parse_cmd_args(ac, av, &args))
        usage(FAIL);
    init_client(&client, &args);
    iniate_handshake(client, &args);
    return 0;
}