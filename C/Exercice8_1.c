#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define PORT 5000
#define MAX 100

typedef struct {
    char nom[50];
    float prix;
} Produit;

int charger_produits(const char *fichier, Produit tab[]) {
    FILE *f = fopen(fichier, "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }

    int n = 0;
    while (fscanf(f, "%s %f", tab[n].nom, &tab[n].prix) == 2) {
        n++;
    }

    fclose(f);
    return n;
}

Produit* chercher_produit(Produit tab[], int n, const char *nom) {
    for (int i = 0; i < n; i++) {
        if (strcmp(tab[i].nom, nom) == 0)
            return &tab[i];
    }
    return NULL;
}

void sauvegarder_commande(const char *client, float total) {
    char filename[100];

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    sprintf(filename, "commande_%04d%02d%02d_%02d%02d%02d.txt",
            tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "Client: %s\nTotal: %.2f\n", client, total);

    fclose(f);
}

void traiter_client(int clientfd, Produit tab[], int n) {
    char buffer[100];
    char nom[50];
    char client[50];
    float total = 0;

    write(clientfd, "Nom du client: ", 16);
    read(clientfd, client, sizeof(client));
    client[strcspn(client, "\r\n")] = 0;

    while (1) {
        write(clientfd, "Produit (fin pour terminer): ", 29);
        int r = read(clientfd, nom, sizeof(nom));
        if (r <= 0) break;

        nom[strcspn(nom, "\r\n")] = 0;

        if (strcmp(nom, "fin") == 0)
            break;

        write(clientfd, "Quantite: ", 10);
        read(clientfd, buffer, sizeof(buffer));
        int qte = atoi(buffer);

        Produit *p = chercher_produit(tab, n, nom);

        if (p) {
            float prix = p->prix * qte;
            total += prix;

            sprintf(buffer, "Ajoute: %.2f\n", prix);
        } else {
            sprintf(buffer, "Produit non trouve\n");
        }

        write(clientfd, buffer, strlen(buffer));
    }

    sprintf(buffer, "TOTAL = %.2f\n", total);
    write(clientfd, buffer, strlen(buffer));

    sauvegarder_commande(client, total);

    close(clientfd);
    exit(0);
}

int main() {
    int sockfd, clientfd;
    struct sockaddr_in serv;

    Produit tab[MAX];
    int n = charger_produits("produits.txt", tab);

    signal(SIGCHLD, SIG_IGN); // éviter zombies

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    printf("Serveur en ecoute sur le port %d...\n", PORT);

    while (1) {
        clientfd = accept(sockfd, NULL, NULL);

        if (fork() == 0) {
            close(sockfd);
            traiter_client(clientfd, tab, n);
        }

        close(clientfd);
    }

    return 0;
}