#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int tube, retour;
    char buffer[256],
         *tube_str = getenv("TUBE_FD");

    if(tube_str == NULL)
    {
        puts("Erreur lors de la recuperation de la variable d'environnement\n");
        retour = 1;
    }
    else
    {
        tube = atoi(tube_str);
        read(tube, buffer, sizeof(buffer));

        printf("Le message du pere: %s\n", buffer);
        close(tube);
        retour = 0;
    }

    return retour;
}