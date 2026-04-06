#coding: utf-8
import os
import sys

pid_fils = os.fork()

if pid_fils == -1:
    print("Erreur lors de la creation du nouveau processus\n")
    sys.exit(1)
    
if pid_fils == 0:
    print(f"Je suis le fils et mon pid est: {os.getpid()}")

else:
    print(f"Je suis le pere et mon pid est: {os.getpid()}")
