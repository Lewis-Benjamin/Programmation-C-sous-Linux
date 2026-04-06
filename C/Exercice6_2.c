#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#define ONE_MB 1048576

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <repertoire1> <repertoire2> ...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        DIR *dir = opendir(argv[i]);
        if (!dir) {
            perror("Erreur ouverture repertoire");
            continue;
        }

        struct dirent *entry;
        printf("Repertoire: %s\n", argv[i]);

        while ((entry = readdir(dir)) != NULL) {
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", argv[i], entry->d_name);

            struct stat st;
            if (stat(path, &st) == -1)
                continue;

            if (S_ISREG(st.st_mode) && st.st_size > ONE_MB) {
                printf("Fichier: %s | Taille: %ld | UID: %d\n",
                       entry->d_name,
                       st.st_size,
                       st.st_uid);
            }
        }

        closedir(dir);
    }

    return 0;
}