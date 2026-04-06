#coding: utf-8
import os

pid_fils = [0] * 5

for i in range(5):
    if i == 0:
        pid_fils[i] = os.fork()

    else:
        if pid_fils[i - 1] == 0:
            break
            
        else:
            pid_fils[i] = os.fork()
