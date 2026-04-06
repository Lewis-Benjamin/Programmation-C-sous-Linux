#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    __pid_t pid_fils;
    pid_fils = fork();
    if (pid_fils == -1)
    {
        puts("Erreur lors de la creation du nouveau processus\n");
        exit(1);
    }
    if (pid_fils == 0)
    {
        printf("Je suis le fils et mon pid est: %d\n", getpid());
    }
    else
    {
        printf("Je suis le pere et mon pid est: %d\n", getpid());
    }
    
    return 0;
}