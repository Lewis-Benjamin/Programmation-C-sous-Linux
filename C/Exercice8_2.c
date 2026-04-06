#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define MAX 100

// ===== STRUCTURE =====
typedef struct {
    char ip[50];
    char nom[50];
} ClientAutorise;

// ===== CHARGEMENT =====
int charger_clients(const char *fichier, ClientAutorise tab[]) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    int n = 0;

    // supporte les 2 formats (avec ou sans nom)
    while (fscanf(f, "%s %s", tab[n].ip, tab[n].nom) >= 1) {
        if (strlen(tab[n].nom) == 0) {
            strcpy(tab[n].nom, "Client");
        }
        n++;
    }

    fclose(f);
    return n;
}

// ===== RECHERCHE =====
ClientAutorise* chercher_client(ClientAutorise tab[], int n, const char *ip) {
    for (int i = 0; i < n; i++) {
        if (strcmp(tab[i].ip, ip) == 0)
            return &tab[i];
    }
    return NULL;
}

// ===== MAIN =====
int main() {
    int sockfd, clientfd;
    struct sockaddr_in serv, client;
    socklen_t len = sizeof(client);

    ClientAutorise tab[MAX];
    int n = charger_clients("add_autoris.txt", tab);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    printf("Serveur en attente...\n");

    while (1) {
        clientfd = accept(sockfd, (struct sockaddr*)&client, &len);

        char *ip = inet_ntoa(client.sin_addr);
        printf("Connexion de %s\n", ip);

        ClientAutorise *c = chercher_client(tab, n, ip);

        if (!c) {
            printf("Acces refuse pour %s\n", ip);
            write(clientfd, "Acces refuse\n", 13);
            close(clientfd);
            continue;
        }

        // ===== CLIENT AUTORISE =====
        printf("Acces autorise pour %s (%s)\n", ip, c->nom);

        char message[100];
        sprintf(message, "Bienvenue %s !\n", c->nom);

        write(clientfd, message, strlen(message));

        // interaction simple
        write(clientfd, "Connexion acceptee.\n", 20);

        close(clientfd);
    }

    close(sockfd);
    return 0;
}