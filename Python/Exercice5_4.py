#coding: utf-8
import threading
import random
import time
import sys

class Tableau:
    def __init__(self, taille):
        self.taille = taille
        self.tab = None

def generer(taille):
    t = Tableau(taille)
    t.tab = [random.randint(0, 99) for _ in range(taille)]
    return t

def inclusion(T1, T2):
    for val in T1.tab:
        if val not in T2.tab:
            return False
    return True

def annulation():
    while True:
        c = sys.stdin.read(1)
        if c.lower() == 'a':
            print("Programme annulé !")
            sys.exit(0)

def th_generer1():
    global T1
    T1 = generer(t1_size)

def th_generer2():
    global T2
    T2 = generer(t2_size)

t1_size = 5
t2_size = 10

T1 = None
T2 = None

t1 = threading.Thread(target=th_generer1)
t2 = threading.Thread(target=th_generer2)
t_annul = threading.Thread(target=annulation, daemon=True)

t1.start()
t2.start()
t_annul.start()

t1.join()
t2.join()

res = inclusion(T1, T2)

print("T1 :", " ".join(map(str, T1.tab)))
print("T2 :", " ".join(map(str, T2.tab)))

if res:
    print("T1 est inclus dans T2")
else:
    print("T1 n'est pas inclus dans T2")