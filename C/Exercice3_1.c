#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int a, b;
    if(argc == 1)
    {
        printf("Vous n'avez entrer aucun arguments\n");
        exit(0);
    }
    else if(argc >= 2)
    {
        printf("Vous avez entre %d arguments\n", argc);
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        printf("L'addition des chiffres que vous avez entre est: %d + %d = %d\n", a, b, a+b);
    }
    return 0;
}