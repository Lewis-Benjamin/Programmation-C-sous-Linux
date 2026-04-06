#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 5

int main() {
    __pid_t fils[N];

    for (int i = 0; i < N; i++) {
        fils[i] = fork();

        if (fils[i] == 0) {
            // ===== FILS =====
            while (1) {
                printf("Fils %d actif (PID=%d)\n", i, getpid());
                sleep(2);
            }
        }
    }

    // ===== PERE =====
    char cmd;
    int num;

    while (1) {
        printf("\nMenu:\n");
        printf("s: endormir | r: reveiller | t: terminer\n");
        printf("Choix + numero fils (0-4): ");
        scanf(" %c %d", &cmd, &num);

        if (num < 0 || num >= N) {
            printf("Numero invalide\n");
            continue;
        }

        if (cmd == 's') {
            kill(fils[num], SIGSTOP);
        } else if (cmd == 'r') {
            kill(fils[num], SIGCONT);
        } else if (cmd == 't') {
            kill(fils[num], SIGTERM);
        } else {
            printf("Commande inconnue\n");
        }
    }

    return 0;
}