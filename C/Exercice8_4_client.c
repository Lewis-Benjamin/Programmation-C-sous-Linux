#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <serveur_ip> <repertoire>\n", argv[0]);
        return 1;
    }

    char *server_ip = argv[1];
    char *rep = argv[2];
    char tmpfile[256];

    // Création archive compressée gzip
    sprintf(tmpfile, "/tmp/rep.tgz");

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "tar zcvf %s -C %s .", tmpfile, rep);

    printf("Création de l'archive %s ...\n", tmpfile);
    if (system(cmd) != 0) {
        fprintf(stderr, "Erreur creation archive\n");
        return 1;
    }

    FILE *fin = fopen(tmpfile, "rb");
    if (!fin) {
        perror("fopen");
        return 1;
    }

    // Envoi de l'archive au serveur
    int sockfd;
    struct sockaddr_in serv;
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(5003);
    inet_pton(AF_INET, server_ip, &serv.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("connect");
        fclose(fin);
        return 1;
    }

    int n;
    while ((n = fread(buffer, 1, BUF_SIZE, fin)) > 0) {
        write(sockfd, buffer, n);
    }

    printf("Archive envoyée au serveur.\n");

    fclose(fin);
    close(sockfd);

    // Suppression du fichier temporaire
    remove(tmpfile);

    return 0;
}