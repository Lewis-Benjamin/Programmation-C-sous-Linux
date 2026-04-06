#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    __pid_t fils;
    int choix = 0;
    char cmd1[256], cmd2[256], fichier[64], sortie[64];

    if (argc == 1)
    {
        printf("Aucun argument n'a ete saisi\n");
        exit(0);
    }
    else if (argc >= 2)
    {
        fils = fork();
        if (fils == -1)
        {
            puts("Erreur lors de la creation du nouveau processus\n");
            exit(0);
        }
        if (fils == 0)
        {
            for (int i = 1; i < argc; i++)
            {
                snprintf(cmd1, sizeof(cmd1), "cp %s ../Fichier/", argv[i]);
                system(cmd1);
                printf("%s a ete copie avec succes\n", argv[i]);
            }
            
            execlp("gcc", "gcc", "test_2.c", "-o", argv[0], NULL);
            exit(0);
        }
        else
        {
            wait(NULL);
            snprintf(sortie, sizeof(sortie), "./%s", argv[0]);
            printf("Entrez un des options possibles:\n\t(1) Continuer a copier\n\t(2) Quitter\n");
            scanf("%d", &choix);
            if(choix == 1)
            {
                printf("Entrez un fichier a copier(et un seul): ");
                scanf("%s", fichier);
                execl(sortie, argv[0], fichier, NULL);
            }
            else if (choix == 2)
                exit(1);
            else 
            {
                printf("%d ne fais pas partie des choix disponoble\n", choix);
                execl(sortie, argv[0], fichier, NULL);
            }
        }
    }
    
    return 0;
}
