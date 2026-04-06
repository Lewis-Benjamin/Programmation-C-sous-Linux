#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 5

__pid_t fils[N];

// Handler pour les fils
void handler_fils(int sig) {
    printf("Fils (PID=%d) termine proprement\n", getpid());
    exit(0);
}

// Handler pour le père
void handler_pere(int sig) {
    printf("\nPere termine !\n");

    // tuer tous les fils
    for (int i = 0; i < N; i++) {
        kill(fils[i], SIGTERM);
    }

    exit(0);
}

int main() {
    signal(SIGTERM, handler_pere);

    for (int i = 0; i < N; i++) {
        fils[i] = fork();

        if (fils[i] == 0) {
            signal(SIGTERM, handler_fils);

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