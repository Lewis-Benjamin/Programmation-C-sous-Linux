#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int tube[2];
    __pid_t fils;
    char tube_str[10],
         message[] = "Bonjour depuis le pere !";

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
        if(fils == 0)
        {
            close(tube[1]);
            sprintf(tube_str, "%d\n", tube[0]);
            setenv("TUBE_FD", tube_str, 1);
            char *args[] = {"./fils", tube_str, NULL};
            execv("./fils", args);
            exit(1);
        }
        else
        {
            close(tube[0]);

            write(tube[1], message, sizeof(message));
            close(tube[1]);
        }
    }

    return 0;
}