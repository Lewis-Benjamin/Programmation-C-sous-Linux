#coding: utf-8
import os
import sys

tube_str = os.environ.get("TUBE_FD")
if tube_str is None:
    print("Erreur lors de la recuperation de la variable d'environnement\n")
    sys.exit(1)

tube = int(tube_str)
buffer = os.read(tube, 256).decode()
print(f"Le message du pere: {buffer}")
os.close(tube)

sys.exit(0)