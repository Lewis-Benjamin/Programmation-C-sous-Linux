#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    __pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // ===== FILS =====
        printf("Fils lancé (PID = %d)\n", getpid());

        while (1) {
            // Calcul infini (simulation)
            printf("Fils travaille...\n");
            sleep(1);
        }
    } else {
        // ===== PERE =====
        char c;

        printf("Commandes:\n");
        printf("s = suspendre\n");
        printf("r = reprendre\n");
        printf("q = quitter\n");

        while (1) {
            printf("> ");
            scanf(" %c", &c);

            if (c == 's') {
                kill(pid, SIGSTOP);
                printf("Fils suspendu\n");
            }
            else if (c == 'r') {
                kill(pid, SIGCONT);
                printf("Fils repris\n");
            }
            else if (c == 'q') {
                kill(pid, SIGKILL);
                printf("Fils terminé\n");
                break;
            }
            else {
                printf("Commande inconnue\n");
            }
        }
    }

    return 0;
}