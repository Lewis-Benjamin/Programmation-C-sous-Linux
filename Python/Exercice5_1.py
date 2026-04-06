#coding: utf-8
import threading

def afficher_tableau(tab):
    print("Tableau :", " ".join(map(str, tab)))

tableau = [1, 2, 3, 4, 5]
thread = threading.Thread(target=afficher_tableau, args=(tableau,))
thread.start()
thread.join()