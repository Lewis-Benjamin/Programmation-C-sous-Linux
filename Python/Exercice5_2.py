#coding: utf-8
import threading
import random
import time

TAILLE = 10
resultat = []

def generer_tableau():
    return [random.randint(0, 99) for _ in range(TAILLE)]

def run():
    global resultat
    resultat = generer_tableau()

random.seed(time.time())

thread = threading.Thread(target=run)
thread.start()
thread.join()

print("Tableau généré :", " ".join(map(str, resultat)))