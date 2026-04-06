#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <serveur_ip> <fichier>\n", argv[0]);
        return 1;
    }

    char *server_ip = argv[1];
    char *filepath = argv[2];

    FILE *fin = fopen(filepath, "r");
    if (!fin) {
        perror("fopen");
        return 1;
    }

    int sockfd;
    struct sockaddr_in serv;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5001);
    inet_pton(AF_INET, server_ip, &serv.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("connect");
        fclose(fin);
        return 1;
    }

    // Envoi du fichier
    int n;
    while ((n = fread(buffer, 1, BUF_SIZE, fin)) > 0) {
        write(sockfd, buffer, n);
    }

    printf("Fichier envoyé au serveur.\n");

    fclose(fin);
    close(sockfd);
    return 0;
}