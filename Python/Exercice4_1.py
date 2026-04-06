#coding: utf-8
import os
import sys

r, w = os.pipe()
fils = os.fork()

if fils == -1:
    print("Erreur dans fork")
    sys.exit(0)

if fils == 0:
    os.close(r)
    mot = input("Veuillez entrer un mot pour la recherche: ")
    os.write(w, mot.encode())
    os.close(w)
else:
    os.wait()
    os.close(w)
    bufferR = os.read(r, 256).decode().strip()
    os.close(r)

    nomfichier = "./text.txt"
    trouve = False
    try:
        with open(nomfichier, "r") as f:
            for ligne in f:
                for mot in ligne.split():
                    if mot == bufferR:
                        print(f'Le mot "{bufferR}" est dans le texte')
                        trouve = True
                        break
                if trouve:
                    break
        if not trouve:
            print(f'Le mot "{bufferR}" n\'est pas dans le texte')
    except FileNotFoundError:
        print("Fichier text.txt introuvable")