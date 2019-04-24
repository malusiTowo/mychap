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

unsigned short csum(unsigned short *buf, int nwords)
{
    unsigned long sum;
    for (sum = 0; nwords > 0; nwords--)
            sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

void configure_socket(client *client, cmd_args *args)
{
    int opt = 1;
    client->_config->sin_family = AF_INET;
    client->_config->sin_addr.s_addr = inet_addr(args->ip);
    client->_config->sin_port = htons(atoi(args->port));

    if (setsockopt(client->sock, IPPROTO_IP, IP_HDRINCL,
    &opt, sizeof(opt)) < SUCCESS) {
        perror("setsockopt");
        exit(FAIL);
    }
}

void configure_headers(client *client, cmd_args *args, char *data)
{
    client->_ip4->ihl = 5;
    client->_ip4->version = 4;
    client->_ip4->tos = 0;
    client->_ip4->tot_len = sizeof(struct iphdr) +
    sizeof(struct udphdr) + PACKET_LEN;
    client->_ip4->id = htons(5000);
    client->_ip4->frag_off = 0;
    client->_ip4->ttl = 255;
    client->_ip4->protocol = IPPROTO_UDP;
    client->_ip4->saddr = INADDR_ANY;
    client->_ip4->daddr = client->_config->sin_addr.s_addr;
    client->_ip4->check = csum((unsigned short *)data, client->_ip4->tot_len);
    client->_udp->len = htons(8 + strlen(data));
    client->_udp->source = INADDR_ANY;
    client->_udp->dest = htons(atoi(args->port));
    client->_udp->check = csum((unsigned short *)(data),
    sizeof(struct iphdr) + sizeof(struct udphdr));
}

void init_client(client *client, cmd_args *args)
{
    if ((client->_config = malloc(sizeof(struct sockaddr_in))) == NULL) {
        perror("malloc");
        exit(FAIL);
    }
    if (!args->ip || !args->port || !args->password)
        exit(FAIL);
    client->_ip4 = malloc(sizeof(struct iphdr));
    client->_udp = malloc(sizeof(struct udphdr));
    if (!client->_ip4 || !client->_udp) {
        perror("malloc");
        exit(FAIL);
    }
    create_socket(client);
    configure_socket(client, args);
}