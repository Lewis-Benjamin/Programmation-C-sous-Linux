#coding: utf-8
import sys
import os
import subprocess

if len(sys.argv) == 1:
    print("Vous n'avez saisi aucun argument")
    sys.exit(0)

n = int(sys.argv[1])
k = int(sys.argv[2])

if k == 0 or k == n:
    print(1)
    
elif n < k:
    print("Le premier argument doit etre plus grand que le second")

else:
    file_1 = f"./temp/res_{n}_{k}_1.txt"
    file_2 = f"./temp/res_{n}_{k}_2.txt"

    cmd1 = f"./{sys.argv[0]} {n-1} {k} > {file_1}"
    cmd2 = f"./{sys.argv[0]} {n-1} {k-1} > {file_2}"

    subprocess.run(cmd1, shell=True)
    subprocess.run(cmd2, shell=True)

    with open(file_1, "r") as f1, open(file_2, "r") as f2:
        a = int(f1.read().strip())
        b = int(f2.read().strip())

    print(a + b)