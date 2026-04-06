#coding: utf-8
import threading
import random
import time
import sys

compt = 0
lock = threading.Lock()
limite = 0

def incrementer():
    global compt
    while True:
        with lock:
            if compt >= limite:
                break
            compt += 1
            print(f"[Thread incrémentation] compteur = {compt}")
        t = random.randint(1, 5)
        time.sleep(t)

def afficher():
    global compt
    while True:
        time.sleep(2)
        with lock:
            if compt >= limite:
                break
            print(f"[Thread affichage] compteur = {compt}")

global limite
if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <valeur_limite>")
    return

limite = int(sys.argv[1])
if limite <= 0:
    print("La limite doit être un entier positif.")
    return

random.seed(time.time())

t1 = threading.Thread(target=incrementer)
t2 = threading.Thread(target=afficher)

t1.start()
t2.start()

t1.join()
t2.join()

print(f"Compteur final = {compt}")