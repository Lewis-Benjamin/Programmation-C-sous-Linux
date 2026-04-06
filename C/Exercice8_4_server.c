#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5003
#define BUF_SIZE 4096

int main() {
    int sockfd, clientfd;
    struct sockaddr_in serv, client;
    socklen_t len = sizeof(client);
    char buffer[BUF_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    printf("Serveur en écoute sur le port %d...\n", PORT);

    while (1) {
        clientfd = accept(sockfd, (struct sockaddr*)&client, &len);
        if (clientfd < 0) continue;

        if (fork() == 0) { // Processus fils pour multi-client
            close(sockfd);

            char *ip = inet_ntoa(client.sin_addr);
            printf("Connexion de %s\n", ip);

            char archive_file[256];
            sprintf(archive_file, "/tmp/%s_rep.tgz", ip);

            FILE *fout = fopen(archive_file, "wb");
            if (!fout) {
                perror("fopen");
                close(clientfd);
                exit(1);
            }

            int n;
            while ((n = read(clientfd, buffer, BUF_SIZE)) > 0) {
                fwrite(buffer, 1, n, fout);
            }

            fclose(fout);
            close(clientfd);

            // Extraction dans le répertoire serveur
            char cmd[512];
            sprintf(cmd, "cd /home/save/ ; tar zxvf %s ; rm %s", archive_file, archive_file);
            system(cmd);

            printf("Archive extraite dans /home/save/ et supprimée.\n");
            exit(0);
        }

        close(clientfd);
    }

    close(sockfd);
    return 0;
}