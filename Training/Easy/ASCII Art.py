import sys
import math

l,h,t = int(input()),int(input()),input()
n,lettres,aff=len(t),[],[]
actual = 0

for i in range(h):
    row = input()
    for x in range(len(row)):
        lettres.append([])
        lettres[x].append("")
    for k in range(27):
        lettres[k][actual]+=row[k*l:(k+1)*l]
    actual+=1

for i in range(n):
    if (ord(t[i]) >= ord('a') and ord(t[i]) <= ord('z')) or (ord(t[i]) >= ord('A') and ord(t[i]) <= ord('Z')):
        lettre=ord(t[i].lower())-97 # Emplacement alphabétique de la i-ème lettre
    else:
        lettre=26
    for i in range(h):
        aff.append("")
        aff[i]+=lettres[lettre][i]

for k in range(h):
    print(aff[k])
