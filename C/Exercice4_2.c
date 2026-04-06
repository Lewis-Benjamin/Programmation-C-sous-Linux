#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int tube[2];
    char buffer[100];
    __pid_t fils;

    if(pipe(tube) != 0)
    {
        puts("Erreur lors de pipe\n");
        exit(0);
    }
    else
    {
        fils = fork();
        if(fils == -1)
        {
            puts("Erreur lors de fork\n");
            exit(0);
        }
        if (fils == 0)
        {
            close(tube[0]);
            dup2(tube[1], STDOUT_FILENO);
            printf("Bonjour depuis le fils\n");

        }
        else 
        {
            close(tube[1]);
            dup2(tube[0], STDIN_FILENO);
            fgets(buffer, sizeof(buffer), stdin);
            printf("Reçu: %s", buffer);
        }
    }
    return 0;
}