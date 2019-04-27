/*
** EPITECH PROJECT, 2018
** IP UDP HEADERS
** File description:
** IP UDP HEADERS
*/

#include "global.h"
#include "chap.h"

void configure_headers(client *client, cmd_args *args,
char *data, int packet_len)
{
    configure_ip_header(client, data, packet_len);
    configure_udp_header(client, args, packet_len);
}

struct sockaddr_in get_client_sock_info(client *client)
{
    struct sockaddr_in info;
    socklen_t len = sizeof(struct sockaddr_in);
    getsockname(client->sock, (struct sockaddr *)&info, &len);
    return info;
}

void configure_ip_header(client *client, char *data, int packet_len)
{
    client->_ip4->ihl = 5;
    client->_ip4->version = 4;
    client->_ip4->tos = 0;
    client->_ip4->tot_len = sizeof(struct iphdr) +
    sizeof(struct udphdr) + packet_len;
    client->_ip4->id = htons(rand());
    client->_ip4->frag_off = 0x40;
    client->_ip4->ttl = 255;
    client->_ip4->protocol = IPPROTO_UDP;
    client->_ip4->check = 0;
    client->_ip4->saddr = client->sock_info.sin_addr.s_addr;
    client->_ip4->daddr = client->_config->sin_addr.s_addr;
    client->_ip4->check =
    csum((unsigned short *)data, client->_ip4->tot_len);
}

void configure_udp_header(client *client, cmd_args *args, int packet_len)
{
    struct pseudo_header psh;
    client->_udp->source = ntohs(client->sock_info.sin_port);
    client->_udp->dest = htons(atoi(args->port));
    client->_udp->len = htons(8 + packet_len);
    client->_udp->check = 0;
    psh.source_address = inet_addr(args->ip);
    psh.dest_address = client->_config->sin_addr.s_addr;
    psh.placeholder = 0;
    psh.protocol = IPPROTO_UDP;
    psh.udp_length = htons(sizeof(struct udphdr) + packet_len);
    int psize = sizeof(struct pseudo_header) +
    sizeof(struct udphdr) + packet_len;
    char *pseudogram = malloc(psize);
    memcpy(pseudogram , (char *) &psh , sizeof(struct pseudo_header));
    memcpy(pseudogram +
    sizeof(struct pseudo_header) , client->_udp ,
    sizeof(struct udphdr) + packet_len);
    client->_udp->check = csum((unsigned short *)pseudogram, psize);
}
