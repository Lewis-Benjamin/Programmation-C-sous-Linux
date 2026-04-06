#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("data.bin", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    int n = size / sizeof(int);

    int *tab = malloc(n * sizeof(int));
    if (!tab) {
        perror("malloc");
        close(fd);
        return 1;
    }

    read(fd, tab, size);

    close(fd);

    printf("Contenu du tableau (%d entiers):\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    free(tab);
    return 0;
}