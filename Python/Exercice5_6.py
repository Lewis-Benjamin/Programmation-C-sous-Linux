#coding: utf-8
import threading
import random
import time

N = 100
tableau = [0.0] * N
lock = threading.Lock()

def moyenne():
    while True:
        with lock:
            tmp = tableau[:]
            tmp[0] = tableau[0]
            tmp[N-1] = tableau[N-1]
            for i in range(1, N-1):
                tmp[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0
            for i in range(1, N-1):
                tableau[i] = tmp[i]
        t = random.randint(1, 3)
        time.sleep(t)

def afficher():
    while True:
        time.sleep(4)
        with lock:
            print("Tableau :", " ".join(f"{x:.2f}" for x in tableau))

random.seed(time.time())
tableau[0] = 0.0
tableau[N-1] = 0.0
for i in range(1, N-1):
    tableau[i] = random.random() * 100

t1 = threading.Thread(target=moyenne)
t2 = threading.Thread(target=afficher)
t1.daemon = True
t2.daemon = True
t1.start()
t2.start()

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass