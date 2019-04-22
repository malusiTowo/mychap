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
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <openssl/sha.h>

#define INIT_MSG "client hello"
#define PACKET_LEN 1024

/* HEADERS */

typedef struct udp_header_t
{
    unsigned short int udph_srcport;
    unsigned short int udph_destport;
    unsigned short int udph_len;
    unsigned short int udph_chksum;
} udp_header;

typedef struct ip4_header_t
{
    unsigned char      iph_header_len;
    unsigned char      ip_version;
    unsigned char      iph_type_service;
    unsigned short int iph_total_len;
    unsigned short int iph_identifier;
    unsigned char      iph_flag;
    unsigned short int iph_offset;
    unsigned char      iph_ttl;
    unsigned char      iph_protocol;
    unsigned short int iph_chksum;
    unsigned int       iph_sourceip;
    unsigned int       iph_destip;

} ip4_header;

typedef struct client_t
{
    ip4_header _ip4;
    udp_header _udp;
    struct sockaddr_in *_config;
    int sock;
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
void configure_socket(client *client,cmd_args *args);
void init_client(client *client, cmd_args *args);
void configure_headers(client *client, cmd_args *args);

/* UTILS */
void usage(int code);
void error_handling(int ac, char **av);
void cleanup(client *client, cmd_args *args);

/* AUTH */
void send_msg(client *client, const char *msg);
void create_headers(client *client, cmd_args *args);
void iniate_handshake(client *client, cmd_args *args);

#endif