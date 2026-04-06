#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 5001
#define BUF_SIZE 1024

int main() {
    int sockfd, clientfd;
    struct sockaddr_in serv, client;
    socklen_t len = sizeof(client);
    char buffer[BUF_SIZE];

    // Création socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    printf("Serveur en écoute sur le port %d...\n", PORT);

    while(1) {
        clientfd = accept(sockfd, (struct sockaddr*)&client, &len);
        if (clientfd < 0) continue;

        char *ip = inet_ntoa(client.sin_addr);
        printf("Connexion de %s\n", ip);

        // Création du nom de fichier avec IP et date
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        char filename[256];
        sprintf(filename, "/home/save/%s_%04d_%02d_%02d.txt",
                ip,
                tm->tm_year+1900,
                tm->tm_mon+1,
                tm->tm_mday);

        FILE *fout = fopen(filename, "w");
        if (!fout) {
            perror("fopen");
            close(clientfd);
            continue;
        }

        // Lecture du fichier envoyé par le client
        int n;
        while ((n = read(clientfd, buffer, BUF_SIZE)) > 0) {
            fwrite(buffer, 1, n, fout);
        }

        printf("Fichier sauvegardé : %s\n", filename);

        fclose(fout);
        close(clientfd);
    }

    close(sockfd);
    return 0;
}