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

void error_handling(int ac, char **av)
{
    if (ac != 7)
        exit(FAIL);
}