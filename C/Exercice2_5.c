#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main()
{
    int t1 = 0, t2 = 0;
    __pid_t fils_1, fils_2;

    srand(time(NULL));
    t1 = rand() % 10 + 1;
    t2 = rand() % 10 + 1;

    switch (fils_1 = fork())
    {
        case -1:
            puts("Erreur lors de la creation du nouveau processus\n");
            exit(errno);
            break;
        
        case 0:
            sleep(t1);

            if(t1 > t2)
            {
                printf("Je suis le fils 1 et j'ai attendu le plus longtemps: %ds pour une duree total de %ds\n", t1, t1+t2);
            }
            fils_2 = fork();
            if(fils_2 == -1)
            {
                puts("Erreur lors de la creation du nouveau processus\n");
                exit(errno);
            }
            if(fils_2 == 0)
            {
                sleep(t2);
                if(t2 > t1)
                {
                    printf("Je suis le fils 2 et j'ai attendu le plus longtemps: %ds pour une duree total de %ds\n", t2, t1+t2);
                }
                else if(t1 == t2)
                    printf("Les deux fils ont attenduent le meme temps\n");
            }
            break;

        default:
            wait(NULL);
            wait(NULL);
            break;
    }

    return 0;
}