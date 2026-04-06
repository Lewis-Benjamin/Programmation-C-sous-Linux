#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int tube, retour;
    char buffer[256];

    if(argc < 2)
    {
        puts("Erreur d'argument\n");
        retour = 1;
    }
    else
    {
        tube = atoi(argv[1]);
        read(tube, buffer, sizeof(buffer));

        printf("Le message du pere: %s\n", buffer);
        close(tube);
        retour = 0;
    }

    return retour;
}