#coding: utf-8
import sys
import os

if len(sys.argv) < 2:
    print("Erreur d'argument\n")
    sys.exit(1)

tube = int(sys.argv[1])
buffer = os.read(tube, 256).decode()
print(f"Le message du pere: {buffer}")
os.close(tube)

sys.exit(0)