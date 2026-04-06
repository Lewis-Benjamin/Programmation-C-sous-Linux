#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    __pid_t pid_fils;

    for(int i = 0; i < 5; i++)
    {
        pid_fils = fork();
        if(pid_fils == -1)
        {
            puts("Erreur lors de la creation du nouveau processus\n");
            exit(1);
        }
        if(pid_fils == 0)
        {
            printf("Je suis le fils %d et mon PID est: %d\n", i+1, getpid());
            exit(0);
        }
    }
    sleep(1);
    printf("Je suis le pere et mon PID est: %d\n", getpid());

    return 0;
}