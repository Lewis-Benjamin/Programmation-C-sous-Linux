#coding: utf-8
import os
import sys
import subprocess

if len(sys.argv) == 1:
    print("Vous n'avez entrer aucun arguments")
    sys.exit(0)

fils = os.fork()
if fils == -1:
    print("Erreur\n")
    sys.exit(1)

if fils == 0:
    subprocess.run(f"gedit {sys.argv[1]}", shell=True)
    os.execvp("gcc", ["gcc", "test_2.c", "-o", sys.argv[0]])
    sys.exit(0)
    
else:
    os.wait()
    sortie = f"./{sys.argv[0]}"
    print("Entrez un des options possibles:\n\t(1) Editer\n\t(2) Quitter")
    choix = int(input())

    if choix == 1:
        fichier = input("Entrez un fichier a editer: ")
        os.execv(sortie, [sys.argv[0], fichier])

    elif choix == 2:
        sys.exit(1)

    else:
        print(f"{choix} ne fais pas partie des choix disponible")
        os.execv(sortie, [sys.argv[0], ""])