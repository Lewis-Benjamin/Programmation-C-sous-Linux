#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE 10

// Fonction du thread
void *generer_tableau(void *arg)
{
    int *tab = malloc(TAILLE * sizeof(int));

    if (tab == NULL)
    {
        perror("malloc");
        pthread_exit(NULL);
    }

    // Initialisation aléatoire
    for (int i = 0; i < TAILLE; i++)
    {
        tab[i] = rand() % 100;
    }

    // Retourne le tableau
    return (void *)tab;
}

int main()
{
    pthread_t thread;
    int *resultat;

    srand(time(NULL)); // initialiser le générateur aléatoire

    // Création du thread
    pthread_create(&thread, NULL, generer_tableau, NULL);

    // Récupération du résultat
    pthread_join(thread, (void **)&resultat);

    // Affichage
    printf("Tableau généré : ");
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d ", resultat[i]);
    }
    printf("\n");

    // Libération mémoire
    free(resultat);

    return 0;
}