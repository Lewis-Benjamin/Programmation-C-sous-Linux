#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    int x;
    __pid_t pid;
    FILE *f = fopen("tmp/entier.txt", "w");

    printf("Entrez un entier : ");
    scanf("%d", &x);

    if (!f) {
        perror("fopen");
        return 1;
    }

    fprintf(f, "%d\n", x);
    fclose(f);

    printf("PID du programme affiche : ");
    scanf("%d", &pid);

    kill(pid, SIGUSR1);

    printf("Signal envoyé !\n");

    return 0;
}