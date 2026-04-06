#coding: utf-8
import os
import sys
import subprocess

if len(sys.argv) == 1:
    print("Aucun argument n'a ete saisi")
    sys.exit(0)

fils = os.fork()
if fils == -1:
    print("Erreur lors de la creation du nouveau processus\n")
    sys.exit(0)

if fils == 0:
    for i in range(1, len(sys.argv)):
        subprocess.run(f"cp {sys.argv[i]} ../Fichier/", shell=True)
        print(f"{sys.argv[i]} a ete copie avec succes")
    os.execvp("gcc", ["gcc", "test_2.c", "-o", sys.argv[0]])
    sys.exit(0)

else:
    os.wait()
    sortie = f"./{sys.argv[0]}"
    print("Entrez un des options possibles:\n\t(1) Continuer a copier\n\t(2) Quitter")
    choix = int(input())

    if choix == 1:
        fichier = input("Entrez un fichier a copier(et un seul): ")
        os.execv(sortie, [sys.argv[0], fichier])

    elif choix == 2:
        sys.exit(1)
        
    else:
        print(f"{choix} ne fais pas partie des choix disponible")
        os.execv(sortie, [sys.argv[0], ""])