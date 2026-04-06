#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char commande[256];

    if(argc == 1)
    {
        printf("Vous n'avez entrer aucun arguments\n");
        exit(0);
    }
    else if(argc >= 2)
    {
        snprintf(commande, sizeof(commande), "gedit %s", argv[1]);
        system(commande);
    }
    
    return 0;
}
