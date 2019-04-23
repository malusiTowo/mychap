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
    cmd_args args;

    error_handling(ac);
    if (!parse_cmd_args(ac, av, &args))
        usage(FAIL);
    init_client(&client, &args);
    iniate_handshake(&client, &args);
    cleanup(&client, &args);
    return 0;
}