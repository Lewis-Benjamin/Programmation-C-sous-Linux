#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    __pid_t pid_fils_1, pid_fils_2;
    
    pid_fils_1 = fork();

    if (pid_fils_1 == -1 || pid_fils_2 == -1)
    {
        puts("Erreur lors de la creation du nouveau processus\n");
        exit(1);
    }
    if (pid_fils_1 == 0)
    {
        printf("Je suis le fils 1 et mon PID est: %d\n", getpid());
    }
    else
    {
        pid_fils_2 = fork();
        if (pid_fils_2 == 0)
        {
            printf("Je suis le fils 2 et mon PID est: %d\n", getpid());
        }
        else
        {
            printf("Je suis le pere et mon PID est: %d\n", getpid());
        }
    }
    
    return 0;
}