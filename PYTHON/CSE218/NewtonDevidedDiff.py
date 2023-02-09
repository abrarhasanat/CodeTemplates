
import matplotlib.pyplot as plt
import math
import numpy as np


def RelativeApproxError(Xnew, Xold):
    temp = (Xnew - Xold) / Xnew
    return abs(temp * 100)


def getVAl(l, r, x, y):
    if(l == r):
        return y[l]
    left = getVAl(l, r - 1, x, y)
    right = getVAl(l + 1, r, x, y)
    return (right - left) / (x[r] - x[l])


def F(x1, x, y, n):
    mul = 1
    sum = 0
    for i in range(0, n):
        temp = getVAl(0, i, x, y)
        sum += (temp * mul)
        mul *= (x1 - x[i])
    return sum


print('Calculating mass at t = 25sec for degree 3\n')
x = [19, 22, 26, 28]
y = [1203, 1245, 1378, 1315]

mass3 = F(25, x, y, 4)
print('mass at t = 25sec is ', mass3, ' metric ton\n')

print('Calculating mass at t = 25sec for degree 4\n')
x = [19, 22, 26, 28, 30]
y = [1203, 1245, 1378, 1315, 1475]
mass4 = F(25, x, y, 5)
print('mass at t = 25sec is', mass4, ' metric ton\n')
print('Relative approximated error is ',
      RelativeApproxError(mass4, mass3), '\n')


print('Calculating velocity at t = 25sec for degree 3\n')
x = [19, 22, 26, 28]
y = [3000, 3500, 4000, 4500]
velocity3 = F(25, x, y, 4)
print('velocity at t = 25sec is ', velocity3, ' m/sec\n')

print('Calculating velocity at t = 25sec for degree 4\n')
x = [19, 22, 26, 28, 30]
y = [3000, 3500, 4000, 4500, 5000]
velocity4 = F(25, x, y, 5)
print('veloity at t = 25sec is', velocity4, ' m/sec\n')
print('Relative approximated error is ',
      RelativeApproxError(velocity4, velocity3), '\n')


