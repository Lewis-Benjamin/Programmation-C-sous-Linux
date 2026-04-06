#coding: utf-8
import os
import sys

pid_fils_1 = os.fork()

if pid_fils_1 == -1:
    print("Erreur lors de la creation du nouveau processus\n")
    sys.exit(1)

if pid_fils_1 == 0:
    print(f"Je suis le fils 1 et mon PID est: {os.getpid()}")

else:
    pid_fils_2 = os.fork()
    if pid_fils_2 == -1:
        print("Erreur lors de la creation du nouveau processus\n")
        sys.exit(1)

    if pid_fils_2 == 0:
        print(f"Je suis le fils 2 et mon PID est: {os.getpid()}")
        
    else:
        print(f"Je suis le pere et mon PID est: {os.getpid()}")
