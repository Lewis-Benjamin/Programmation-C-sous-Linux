#coding: utf-8
import os
import sys
import time

for i in range(5):
    pid_fils = os.fork()
    
    if pid_fils == -1:
        print("Erreur lors de la creation du nouveau processus\n")
        sys.exit(1)

    if pid_fils == 0:
        print(f"Je suis le fils {i+1} et mon PID est: {os.getpid()}")
        sys.exit(0)

time.sleep(1)
print(f"Je suis le pere et mon PID est: {os.getpid()}")