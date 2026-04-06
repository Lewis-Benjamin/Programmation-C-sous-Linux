#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char commande[256];

    if(argc == 1)
    {
        printf("Vous n'avez entrer aucun arguments\n");
        exit(0);
    }
    else if(argc >= 2)
    {
        snprintf(commande, sizeof(commande), "cp -r ../Fichier/ %s", argv[1]);
        system(commande);
        printf("Le fichier %s a ete copie avec succes\n");
    }
    return 0;
}