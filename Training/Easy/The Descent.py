import sys
import math

while True:
    hauteurs=[]
    for i in range(8):
        mountain_h = int(input())  # represents the height of one mountain.
        hauteurs.append(mountain_h)
    max=0
    for i in range(8):
        if hauteurs[i]>hauteurs[max]:
            max=i
    print(max)
