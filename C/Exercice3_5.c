#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int choix;
    __pid_t fils;
    char sortie[64], commande[256], fichier[64];
    if(argc == 1)
    {
        printf("Vous n'avez entrer aucun arguments\n");
        exit(0);
    }
    else if(argc >= 2)
    {
        fils = fork();
        if(fils == -1)
        {
            puts("Erreur\n");
            exit(errno);
        }
        if(fils == 0)
        {
            snprintf(commande, sizeof(commande), "gedit %s", argv[1]);
            system(commande);
            execlp("gcc", "gcc", "test_2.c", "-o", argv[0], NULL);
            exit(0);
        }
        else
        {
            wait(NULL);
            snprintf(sortie, sizeof(sortie), "./%s", argv[0]);
            printf("Entrez un des options possibles:\n\t(1) Editer\n\t(2) Quitter\n");
            scanf("%d", &choix);
            if(choix == 1)
            {
                printf("Entrez un fichier a editer: ");
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
