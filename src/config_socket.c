/*
** EPITECH PROJECT, 2018
** CONFIG SOCKET
** File description:
** CONFIG SOCKET
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

void connect_server(client *client, struct sockaddr_in config)
{
    if (connect(client->sock,
    (struct sockaddr *)&config, sizeof(config)) < ERROR) {
        perror("connect");
        exit(FAIL);
    }
}

void init_client(client *client, cmd_args *args)
{
    struct sockaddr_in config;

    if (!args->ip || !args->port || !args->password)
        exit(FAIL);
    create_socket(client);
    configure_socket(client, &config, atoi(args->port));
    connect_server(client, config);
    // send hello msg
    // receive secret
    // hash secret + password
    // send back result to server
}