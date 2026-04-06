#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int n;

    printf("Nombre d'entiers : ");
    scanf("%d", &n);

    int *tab = malloc(n * sizeof(int));
    if (!tab) {
        perror("malloc");
        return 1;
    }

    printf("Entrez les %d entiers :\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tab[i]);
    }

    int fd = open("data.bin", O_WRONLY | O_CREAT | O_TRUNC, 0624);
    if (fd == -1) {
        perror("open");
        free(tab);
        return 1;
    }

    write(fd, tab, n * sizeof(int));

    close(fd);
    free(tab);

    printf("Tableau sauvegardé dans data.bin\n");
    return 0;
}