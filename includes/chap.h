/*
** EPITECH PROJECT, 2018
** CHAP header
** File description:
** header
*/

#ifndef CHAP_H
#define CHAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/wait.h>

typedef struct client_t
{
    int sock;
} client;


typedef struct udp_header_t
{

} udp_header;

typedef struct ip4_header_t
{

} ip4_header;

typedef struct cmd_args_t
{
    char *port;
    char *ip;
    char *password;
} cmd_args;

#endif