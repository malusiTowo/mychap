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
    char *hashed = malloc(sizeof(char) * SHA256_DIGEST_LENGTH);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < 64; i++)
        sprintf(&hashed[2 * i], "%.2x", hash[i]);
    return hashed;
}

void send_msg(client *client, const char *msg)
{
    if (sendto(client->sock, msg, client->_ip4.iph_header_len, 0, (struct sockaddr *)client->_config, sizeof(client->_config)) < SUCCESS) {
        perror("sendto");
        exit(FAIL);
    }
}

char *get_msg(client *client)
{
    char *buffer = malloc(sizeof(char) * PACKET_LEN);
    if (!buffer) {
        perror("malloc");
        exit(FAIL);
    }
    if (recvfrom(client->sock, (char *)buffer, PACKET_LEN, 0,
    (struct sockaddr *)client->_config, sizeof(client->_config)) < SUCCESS) {
        perror("recvfrom");
        exit(FAIL);
    }
    return buffer;
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
    char *secret = NULL, *response = NULL;
    send_msg(client, INIT_MSG);
    secret = get_msg(client);
    secret = sha256_hash(strcat(secret, args->password));
    send_msg(client, secret);
    response = get_msg(client);
    check_challenge_success(response);
}