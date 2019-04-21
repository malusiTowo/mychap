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

#define INIT_MSG "client hello"

/* HEADERS */

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

/* FUNCTION PROTOTYPES */

/* PARSING */
bool parse_cmd_args(int ac, char **av, cmd_args *args);
bool evaluate_opt(int *opt, cmd_args *args);
bool check_ip(const char *str);
bool check_port(const char *str);

/* CONFIG SOCKET */
void create_socket(client *client);
void configure_socket(client *client, struct sockaddr_in *config, int port);
void bind_socket(client *client, struct sockaddr_in *config);
void init_client(client *client, cmd_args *args);

/* UTILS */
void usage(int code);

#endif