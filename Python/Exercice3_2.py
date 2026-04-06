#coding: utf-8
import sys
import subprocess

if len(sys.argv) == 1:
    print("Vous n'avez entrer aucun arguments")
    sys.exit(0)

else:
    commande = f"cp -r ../Fichier/ {sys.argv[1]}"
    subprocess.run(commande, shell=True)
    print("Le fichier a ete copie avec succes")