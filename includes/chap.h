/*
** EPITECH PROJECT, 2018
** CHAP header
** File description:
** header
*/

#ifndef CHAP_H
#define CHAP_H

#define _GNU_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <openssl/sha.h>
#include <getopt.h>


/* HEADERS */

typedef struct client_t
{
    struct iphdr *_ip4;
    struct udphdr *_udp;
    struct sockaddr_in *_config;
    struct sockaddr_in sock_info;
    int sock;
    char *payload;
} client;


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
void configure_socket(client *client, cmd_args *args);
void init_client(client *client, cmd_args *args);
void configure_headers(client *client, cmd_args *args, char *data, int packet_len);
struct sockaddr_in get_client_sock_info(client *client);
void configure_udp_header(client *client, cmd_args *args,
char *data, int packet_len);
void configure_ip_header(client *client, char *data, int packet_len);

/* UTILS */
void usage(int code);
void error_handling(int ac);
void cleanup(client *client, cmd_args *args);
unsigned short csum(unsigned short *buf, int nwords);

/* AUTH */
void send_msg(client *client, const char *msg, cmd_args *args);
void get_msg(client *client, char *msg);
void create_headers(client *client, cmd_args *args);
void iniate_handshake(client *client, cmd_args *args);

#endif