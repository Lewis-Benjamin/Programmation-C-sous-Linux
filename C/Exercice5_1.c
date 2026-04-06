#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Fonction exécutée par le thread
void *afficher_tableau(void *arg)
{
    int *tab = (int *)arg;

    printf("Tableau : ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int main()
{
    pthread_t thread;

    int tableau[5] = {1, 2, 3, 4, 5};

    // Création du thread
    pthread_create(&thread, NULL, afficher_tableau, (void *)tableau);

    // Attendre la fin du thread
    pthread_join(thread, NULL);

    return 0;
}