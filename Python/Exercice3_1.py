#coding: utf-8
import sys

if len(sys.argv) == 1:
    print("Vous n'avez entrer aucun arguments")
    sys.exit(0)
else:
    print(f"Vous avez entre {len(sys.argv)-1} arguments")
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    print(f"L'addition des chiffres que vous avez entre est: {a} + {b} = {a+b}")