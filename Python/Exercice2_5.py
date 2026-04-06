#coding: utf-8
import os
import sys
import time
import random
import errno

t1 = random.randint(1, 10)
t2 = random.randint(1, 10)

fils_1 = os.fork()
if fils_1 == -1:
    print("Erreur lors de la creation du nouveau processus\n")
    sys.exit(errno.EAGAIN)

if fils_1 == 0:
    time.sleep(t1)

    if t1 > t2:
        print(f"Je suis le fils 1 et j'ai attendu le plus longtemps: {t1}s pour une duree total de {t1 + t2}s")

    fils_2 = os.fork()
    if fils_2 == -1:
        print("Erreur lors de la creation du nouveau processus\n")
        sys.exit(errno.EAGAIN)

    if fils_2 == 0:
        time.sleep(t2)
        if t2 > t1:
            print(f"Je suis le fils 2 et j'ai attendu le plus longtemps: {t2}s pour une duree total de {t1 + t2}s")
        elif t1 == t2:
            print("Les deux fils ont attendu le meme temps")
else:
    os.wait()
    os.wait()