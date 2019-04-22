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
    if ((client->sock = socket(AF_INET, SOCK_DGRAM, 0)) == ERROR) {
        perror("socket");
        exit(FAIL);
    }
}

unsigned short csum(unsigned short *buf, int nwords)
{       //
        unsigned long sum;
        for(sum=0; nwords>0; nwords--)
                sum += *buf++;
        sum = (sum >> 16) + (sum &0xffff);
        sum += (sum >> 16);
        return (unsigned short)(~sum);
}

void configure_socket(client *client, cmd_args *args)
{
    int opt = 1;
    client->_config->sin_family = AF_INET;
    client->_config->sin_addr.s_addr = inet_addr(args->ip);
    client->_config->sin_port = htons(args->port);

    configure_headers(client, args);
    if (setsockopt(client->sock, IPPROTO_IP, IP_HDRINCL,
    &opt, sizeof(opt)) < SUCCESS) {
        perror("setsockopt");
        exit(FAIL);
    }
}

void connect_server(client *client)
{
    if (connect(client->sock,
    (struct sockaddr *)client->_config, sizeof(client->_config)) < ERROR) {
        perror("connect");
        exit(FAIL);
    }
}

void configure_headers(client *client, cmd_args *args)
{
    char buf[PACKET_LEN];
    client->_ip4.iph_header_len = 5;
    client->_ip4.ip_version = 4;
    client->_ip4.iph_type_service = 16;
    client->_ip4.iph_total_len = sizeof(ip4_header) + sizeof(udp_header);
    client->_ip4.iph_identifier = htons(5000);
    client->_ip4.iph_ttl = 64;
    client->_ip4.iph_protocol = 17;
    client->_ip4.iph_sourceip = inet_addr("127.0.0.1");
    client->_ip4.iph_destip = inet_addr(args->ip);

    client->_udp.udph_len = sizeof(udp_header);
    client->_udp.udph_chksum = csum((unsigned short *)(buf), sizeof(ip4_header) + sizeof(udp_header));
    client->_udp.udph_srcport = htons(args->port);
    client->_udp.udph_destport = htons(args->port);
}

void init_client(client *client, cmd_args *args)
{
    if (client->_config = malloc(sizeof(struct sockaddr_in)) == NULL) {
        perror("malloc");
        exit(FAIL);
    }
    if (!args->ip || !args->port || !args->password)
        exit(FAIL);
    create_socket(client);
    configure_socket(client,atoi(args->port));
    connect_server(client);
}