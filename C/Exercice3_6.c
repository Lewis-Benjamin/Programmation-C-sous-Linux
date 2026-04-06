#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE *fich1 = NULL, *fich2 = NULL;
    int k, n, a, b;
    char cmd1[256], cmd2[256], file_1[64], file_2[64];

    if(argc == 1)
    {
        printf("Vous n'avez saisi aucun argument\n");
        exit(0);
    }
    else if(argc >= 2)
    {
        n = atoi(argv[1]);
        k = atoi(argv[2]);

        if (k == 0 || k == n)
            printf("1\n");
        else if(n < k)
        {
            printf("Le premier argument doit etre plus grand que le second\n");
            exit(0);
        }
        else
        {
            snprintf(file_1, sizeof(file_1), "./temp/res_%d_%d_1.txt", n, k);
            snprintf(file_2, sizeof(file_2), "./temp/res_%d_%d_2.txt", n, k);

            snprintf(cmd1, sizeof(cmd1), "./%s %d %d > %s ", argv[0], n-1, k, file_1);
            snprintf(cmd2, sizeof(cmd2), "./%s %d %d > %s ", argv[0], n-1, k-1, file_2);

            system(cmd1);
            system(cmd2);

            fich1 = fopen(file_1, "r");
            fich2 = fopen(file_2, "r");

            fscanf(fich1, "%d", &a);
            fscanf(fich2, "%d", &b);

            fclose(fich1);
            fclose(fich2);

            printf("%d\n", a+b);
        }
    }

    return 0;
}