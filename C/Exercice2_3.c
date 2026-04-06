#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    __pid_t pid_fils[5];

    for(int i = 0; i < 5; i++)
    {
        if(i == 0)
        {
            pid_fils[i] = fork();
        }
        else
        {
            if(pid_fils[i - 1] == 0)
            {
                break;
            }
            else
            {
                pid_fils[i] = fork();
            }
        }
    }

    return 0;
}