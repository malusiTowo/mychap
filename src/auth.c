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
    client->payload = strdup(msg);
    configure_headers(client, args, data);
    socklen_t addrlen = sizeof(struct sockaddr_in);

    if (sendto(client->sock, data, client->_ip4->tot_len, 0,
    (struct sockaddr *)client->_config, addrlen) < SUCCESS) {
        perror("sendto");
        exit(FAIL);
    }
}

void get_msg(client *client, char *msg)
{
    int len = 0;
    struct sockaddr_in from;
    socklen_t addrlen = sizeof(from);
    memset(msg, 0, PACKET_LEN);
    memset(&from, 0, sizeof(struct sockaddr_in));

    if ((len = recvfrom(client->sock, msg, sizeof(msg), 0,
    (struct sockaddr *)&from, &addrlen)) < SUCCESS) {
        perror("recvfrom");
        exit(FAIL);
    }
    msg[len] = '\0';
}

void check_challenge_success(char *str)
{
    if (strcmp(str, "KO") == SUCCESS)
        printf("KO\n");
    else
        printf("Secret: '%s'\n", str);
}

void iniate_handshake(client *client, cmd_args *args)
{
    char secret[PACKET_LEN];
    char *response = NULL;
    send_msg(client, INIT_MSG, args);
    get_msg(client, secret);
    char *challenge = strcat(secret, args->password);
    response = sha256_hash(challenge);
    send_msg(client, response, args);
    get_msg(client, secret);
    check_challenge_success(secret);
}