import cmath
import numpy as np
import matplotlib.pyplot as plt

N=45
n=22
aux = 0
aux2 = 0

t = []
for k in range((-1)*n,n+1):
    t.append(2*k/N)

x = []
y = []
for k in range(N):
    if k < (N+1)/2:
        y.append(aux2)
        aux2+=1
    else:
        y.append(aux2)
        aux2-=1

    x.append(2*(aux * 2/N) + 10)
    aux+=1

def T(x):
    if x==0:
         return 1.0
    else:
         denom = N*cmath.sin(cmath.pi*x/2) if N%2==1 else N*cmath.tan(cmath.pi*x/2)
         return cmath.sin(N*cmath.pi*x/2)/denom

def triginterp(t,y):
    p = []
    sum = 0
    for i in range(N):
        for k in range(N):
            sum+=y[k]*T(x[i]-t[k]) 
        p.append(sum)
        sum = 0
    return p

plt.plot(x, triginterp(t,y),'c', label='mimata')
plt.plot(x, y,"ok")

plt.show()

