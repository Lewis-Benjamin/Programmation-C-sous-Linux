#coding: utf-8
import os
import sys

r, w = os.pipe()

os.set_inheritable(r, True)

fils = os.fork()

if fils == -1:
    print("Erreur lors de fork\n")
    sys.exit(1)

if fils == 0:
    os.close(w)
    os.execv(sys.executable, [sys.executable, "Exercice4_3_fils.py", str(r)])
    sys.exit(1)
else:
    os.close(r)
    message = "Bonjour depuis le pere !"
    os.write(w, message.encode())
    os.close(w)