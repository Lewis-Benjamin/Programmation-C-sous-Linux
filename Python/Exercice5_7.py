#coding:utf-8
import threading
import random
import time

u = 1.0
compteur = 0
lock = threading.Lock()

def f1(x):
    return ((x - 1) ** 2) / 4.0

def f2(x):
    return ((x - 2) ** 2) / 6.0

def thread1():
    global u, compteur
    while True:
        with lock:
            compteur += 1
            u = f1(u)
            print(f"[T1] compteur = {compteur}, u = {u:.5f}")
        t = random.randint(1, 5)
        time.sleep(t)

def thread2():
    global u, compteur
    while True:
        with lock:
            compteur += 1
            u = f2(u)
            print(f"[T2] compteur = {compteur}, u = {u:.5f}")
        t = random.randint(1, 5)
        time.sleep(t)

random.seed(time.time())
t1 = threading.Thread(target=thread1)
t2 = threading.Thread(target=thread2)
t1.daemon = True
t2.daemon = True
t1.start()
t2.start()

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass