#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 256

int main()
{
    FILE *file = NULL;
    __pid_t fils;
    int tube[2], i = 0;
    unsigned char bufferR[BUFFER_SIZE] = {0}, bufferW[BUFFER_SIZE] = {0};
    char mot[64], *nomfichier = "./text.txt";

    puts("Creation du tube\n");
    if(pipe(tube) != 0)
    {
        fprintf(stderr, "Erreur dans pipe\n");
        exit(0);
    }
    else
    {
        switch (fils = fork())
        {
            case -1:
                fprintf(stderr, "Erreur dans fork");
                exit(0);
                break;
            
            case 0:
                close(tube[0]);
                printf("Veuillez entrer un mot pour la recherche: ");
                scanf("%s", mot);
                sprintf(bufferW, "%s", mot);
                write(tube[1], bufferW, BUFFER_SIZE);

            default:
                wait(NULL);
                close(tube[1]);
                int n = read(tube[0], bufferR, BUFFER_SIZE);
                file = fopen(nomfichier, "r");
                while (fscanf(file, "%63s", mot) == 1)
                {
                    if(strcmp(mot, bufferR) == 0)
                    {
                        printf("Le mot \"%s\" est dans le texte\n", bufferR);
                        break;
                    }
                    else
                        i = 1;
                }
                if(i == 1)
                    printf("Le mot \"%s\" n'est pas dans le texte\n", bufferR);
                
                break;
        }
    }
    return 0;
}