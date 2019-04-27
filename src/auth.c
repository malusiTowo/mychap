/*
** EPITECH PROJECT, 2018
** AUTH
** File description:
** AUTH
*/

#include "chap.h"
#include "global.h"

char *sha256_hash(char *str)
{
    char *tmp = NULL;
    char *hashed = malloc(sizeof(char) * 64);
    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
    SHA256_CTX sha256;

    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        asprintf(&tmp, "%02x", hash[i]);
        strcat(hashed, tmp);
    }
    hashed[64] = '\0';
    free(tmp);
    return hashed;
}

void send_msg(client *client, const char *msg, cmd_args *args)
{
    char data[4096] = {0};
    client->_ip4 = (struct iphdr *)data;
    client->_udp = (struct udphdr *)(data + sizeof(struct iphdr));
    client->payload = data + sizeof(struct iphdr) + sizeof(struct udphdr);
    strcpy(client->payload, msg);
    configure_headers(client, args, data, strlen(msg));
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (sendto(client->sock, data, client->_ip4->tot_len, 0,
    (struct sockaddr *)client->_config, addrlen) < SUCCESS) {
        perror("sendto");
        exit(FAIL);
    }
}

char *get_msg(client *client)
{
    char *ret = NULL;
    struct udphdr *s;
    char msg[PACKET_LEN];
    int len = 0;

    while (true) {
        memset(msg, 0, PACKET_LEN);
        len = recvfrom(client->sock, msg, PACKET_LEN, 0, NULL, NULL);
        if (len < SUCCESS) {
            perror("recvfrom");
            exit(FAIL);
        }
        s = (struct udphdr *)(msg + sizeof(struct iphdr));
        if (s->source == client->_config->sin_port)
            break;
    }
    ret = msg + sizeof(struct iphdr) + sizeof(struct udphdr);
    return ret;
}

void check_challenge_success(char *str)
{
    if (strncmp(str, "KO", 2) == SUCCESS)
        printf("KO\n");
    else
        printf("Secret: '%s'\n", str);
}

void iniate_handshake(client *client, cmd_args *args)
{
    char *secret = NULL;
    char *response = NULL;
    send_msg(client, INIT_MSG, args);
    secret = get_msg(client);
    char *challenge = strcat(secret, args->password);
    response = sha256_hash(challenge);
    send_msg(client, response, args);
    secret = get_msg(client);
    check_challenge_success(secret);
}
