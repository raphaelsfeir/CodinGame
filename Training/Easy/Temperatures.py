import sys
import math

n = int(input())  # the number of temperatures to analyse
temp = []
for i in input().split():
    # t: a temperature expressed as an integer ranging from -273 to 5526
    t = int(i)
    temp.append(t)

if temp!=[]:
    diff=[] # Tableau des différences par rapport à 0
    for i in temp:
        diff.append(abs(0-i))
    min = 0 # On cherche la température ayant la plus petite distance par rapport à 0
    for i in range(len(temp)):
        if diff[i]<diff[min]:
            min = i
    if temp[min] <0:
        for i in range(len(temp)):
            if temp[i]==-temp[min]:
                min=i
                break
    print(temp[min])
else:
    print(0)
