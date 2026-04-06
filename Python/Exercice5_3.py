#coding: utf-8
import threading
import random
import time

class TypeTableau:
    def __init__(self, taille, x=None):
        self.taille = taille
        self.x = x
        self.tab = None

def generer(taille):
    t = TypeTableau(taille)
    t.tab = [random.randint(0, 99) for _ in range(taille)]
    return t

def rechercher(t):
    for val in t.tab:
        if val == t.x:
            return True
    return False

def th_generer():
    global t
    t = generer(taille)

random.seed(time.time())
taille = int(input("Donner la taille du tableau : "))
x = int(input("Donner x : "))

t = None

thread_gen = threading.Thread(target=th_generer)
thread_gen.start()
thread_gen.join()

t.x = x
res = rechercher(t)

print("Tableau :", " ".join(map(str, t.tab)))
if res:
    print("x est dans le tableau")
else:
    print("x n'est pas dans le tableau")