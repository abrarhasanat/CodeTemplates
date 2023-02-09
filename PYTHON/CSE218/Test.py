from numpy.testing._private.utils import import_nose
import matplotlib.pyplot as plt
import numpy as np
import math

ans = 0


def getA(x, y, b):
    sum1 = 0
    sum2 = 0
    sum3 = 0
    n = len(x)
    for i in range(0, n):
        sum1 += (y[i] * math.exp(x[i]))
        sum2 += (b * math.exp(2 * x[i]))
        sum3 += (x[i] * math.exp(x[i]))
    return (sum1 - sum2) / sum3


def f(x, y, b):
   n = len(x)
   sum1 = 0
   sum2 = 0
   sum3 = 0
   a = getA(x, y, b)
   for i in range(0, n):
       sum1 += x[i] * y[i] ; 
       sum2 += a * x[i] * x[i]
       sum3 += b * x[i] * math.exp(x[i])
   return (sum2 + sum3) - sum1

    


def RelativeApproxError(Xnew, Xold):
    if(Xnew == 0) : 
        return 1000 
    temp = (Xnew - Xold) / Xnew
    return abs(temp * 100)


def bisect(lower_bound, upper_bound, expected_approx_error, max_iteration_number , x , y):
    old_mid = 100 * 100
    for i in range(1, max_iteration_number + 1):
        new_mid = (lower_bound + upper_bound) / 2
        F_mid = f( x, y , new_mid)
        F_left = f(x,  y, lower_bound)
        temp = F_left * F_mid
        if temp < 0:
            upper_bound = new_mid
        else:
            lower_bound = new_mid

        global ans
        ans = new_mid
        if(RelativeApproxError(new_mid, old_mid) < expected_approx_error):
            break
        old_mid = new_mid
        if temp == 0:
            break
        if i + 1 == max_iteration_number:
            print("Probably We should Increase Iteration Number")


def function(a ,b, x):
    return a * x + b * math.exp(x)

pos_x = []
pos_y = []

min_x = -1000
max_x = 1000
with open('data.txt') as ff:
    while True:
        line = ff.readline()
        if not line:
            break
        lst = line.split(' ')
        pos_x.append(float(lst[0]))
        pos_y.append(float(lst[1]))

n = len(pos_x)
for i in range(0, n):
    plt.scatter(pos_x[i], pos_y[i], 10, color='red')



bisect(min_x , max_x , 0.005 , 100000 ,pos_x , pos_y)
b = ans ; 
a = getA(pos_x, pos_y , b) 


print('a = ', a , '\nb = ' ,b , '\n')
xs = np.arange(0 , 2 , 0.00005)
ys = []
for i in xs:
    ys.append(function(a ,b, i))


plt.plot(xs, ys, color='green', linestyle='dashed',
         linewidth='3', label='Equation')


n = len(pos_x) 
for i in range(0 , n ) :
    plt.scatter(pos_x[i] , pos_y[i] , 10 ,color = 'red')

plt.grid(True, which='both')
plt.xlabel('Size of array')
plt.title('Ascending')
plt.ylabel('Time(ms)')
plt.legend()
plt.show()
