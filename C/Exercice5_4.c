#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

typedef struct
{
    int *tab;
    int taille;
} Tableau;

// Génération aléatoire
void *generer(void *arg)
{
    int taille = *((int *)arg);

    Tableau *t = malloc(sizeof(Tableau));
    t->taille = taille;
    t->tab = malloc(taille * sizeof(int));

    for (int i = 0; i < taille; i++)
    {
        t->tab[i] = rand() % 100;
    }

    return (void *)t;
}

// Vérifie si T1 ⊂ T2
void *inclusion(void *arg)
{
    Tableau **tabs = (Tableau **)arg;
    Tableau *T1 = tabs[0];
    Tableau *T2 = tabs[1];

    int *res = malloc(sizeof(int));
    *res = 1;

    for (int i = 0; i < T1->taille; i++)
    {
        int trouve = 0;

        for (int j = 0; j < T2->taille; j++)
        {
            if (T1->tab[i] == T2->tab[j])
            {
                trouve = 1;
                break;
            }
        }

        if (!trouve)
        {
            *res = 0;
            break;
        }
    }

    return (void *)res;
}

void *annulation(void *arg)
{
    char c;
    printf("Appuyez sur 'A' pour annuler...\n");

    while (1)
    {
        c = getchar();
        if (c == 'A' || c == 'a')
        {
            printf("Programme annulé !\n");
            exit(0);
        }
    }
}

int main() {
    pthread_t th1, th2, th3, th4;

    int t1_size = 5;
    int t2_size = 10;

    Tableau *T1, *T2;
    int *res;

    srand(time(NULL));

    // Threads génération
    pthread_create(&th1, NULL, generer, &t1_size);
    pthread_create(&th2, NULL, generer, &t2_size);

    // Thread annulation
    pthread_create(&th4, NULL, annulation, NULL);

    // Attente génération
    pthread_join(th1, (void **)&T1);
    pthread_join(th2, (void **)&T2);

    // Préparer argument
    Tableau *tabs[2] = {T1, T2};

    // Thread inclusion
    pthread_create(&th3, NULL, inclusion, tabs);
    pthread_join(th3, (void **)&res);

    // Affichage
    printf("T1 : ");
    for (int i = 0; i < T1->taille; i++)
        printf("%d ", T1->tab[i]);

    printf("\nT2 : ");
    for (int i = 0; i < T2->taille; i++)
        printf("%d ", T2->tab[i]);

    printf("\n");

    if (*res)
        printf("T1 est inclus dans T2\n");
    else
        printf("T1 n'est pas inclus dans T2\n");

    // Libération
    free(T1->tab); free(T1);
    free(T2->tab); free(T2);
    free(res);

    return 0;
}
