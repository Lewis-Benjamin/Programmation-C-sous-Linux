#coding: utf-8
import os
import sys

r, w = os.pipe()
fils = os.fork()

if fils == -1:
    print("Erreur lors de fork\n")
    sys.exit(0)

if fils == 0:
    os.close(r)
    os.dup2(w, sys.stdout.fileno())
    print("Bonjour depuis le fils")
    os.close(w)
    
else:
    os.close(w)
    os.dup2(r, sys.stdin.fileno())
    buffer = sys.stdin.read()
    print(f"Reçu: {buffer}")
    os.close(r)