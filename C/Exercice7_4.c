#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int *tab;
int n;

void handler(int sig) {
    printf("\nErreur: indice invalide (segmentation fault)\n");
}

int main() {
    int i;

    signal(SIGSEGV, handler);

    printf("Taille du tableau: ");
    scanf("%d", &n);

    tab = malloc(n * sizeof(int));
    if (!tab) {
        perror("malloc");
        return 1;
    }

    printf("Entrez les %d elements:\n", n);
    for (int j = 0; j < n; j++) {
        scanf("%d", &tab[j]);
    }

    while (1) {
        printf("Indice i: ");
        scanf("%d", &i);

        // accès direct (peut provoquer SIGSEGV)
        printf("tab[%d] = %d\n", i, tab[i]);
        break;
    }

    free(tab);
    return 0;
}