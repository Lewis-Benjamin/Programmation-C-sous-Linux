#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct
{
    int *tab;
    int taille;
    int x;
} TypeTableau;

void *generer(void *arg)
{
    int taille = *((int *)arg);

    TypeTableau *t = malloc(sizeof(TypeTableau));
    t->taille = taille;
    t->tab = malloc(taille * sizeof(int));

    for (int i = 0; i < taille; i++)
    {
        t->tab[i] = rand() % 100;
    }

    return (void *)t;
}

void *rechercher(void *arg)
{
    TypeTableau *t = (TypeTableau *)arg;

    int *result = malloc(sizeof(int));
    *result = 0;

    for (int i = 0; i < t->taille; i++)
    {
        if (t->tab[i] == t->x)
        {
            *result = 1;
            break;
        }
    }

    return (void *)result;
}

int main()
{
    pthread_t th1, th2;
    TypeTableau *t;
    int taille, x;
    int *res;

    srand(time(NULL));

    printf("Donner la taille du tableau : ");
    scanf("%d", &taille);

    // Thread génération
    pthread_create(&th1, NULL, generer, &taille);

    // Lecture de x en parallèle
    printf("Donner x : ");
    scanf("%d", &x);

    // Attendre la fin du thread 1
    pthread_join(th1, (void **)&t);

    // Injecter x dans la structure
    t->x = x;

    // Thread recherche
    pthread_create(&th2, NULL, rechercher, t);

    pthread_join(th2, (void **)&res);

    // Affichage
    printf("Tableau : ");
    for (int i = 0; i < t->taille; i++)
    {
        printf("%d ", t->tab[i]);
    }
    printf("\n");

    if (*res == 1)
        printf("x est dans le tableau\n");
    else
        printf("x n'est pas dans le tableau\n");

    // Libération
    free(t->tab);
    free(t);
    free(res);

    return 0;
}
