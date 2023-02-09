import math
from typing_extensions import IntVar


def f(m0, q, u, t):
   return q*t + u ;


def RelativeApproxError(Xnew, Xold):
    temp = (Xnew - Xold) / Xnew
    return abs(temp * 100)


def IntegrateTrapezoid(m0, q, u, ti, tf, n):
    dellx = (tf - ti) / n
    ans = f(m0, q, u, ti) + f(m0, q, u, tf)
    for i in range(1, n):
        ans += 2.0 * (f(m0, q, u, ti + i * dellx))
    return ans * (dellx / 2.00)


def IntegrateSimpsons13(m0, q, u, ti, tf, n):
    dellx = (tf - ti) / n
    ans = 0
    for i in range(0, n + 1):
        x = ti + i * dellx
        if(i == 0 or i == n):
            ans += f(m0, q, u, x)
        elif i % 2 != 0:
            ans += 4.0 * f(m0, q, u, x)
        else:
            ans += 2.0 * f(m0, q, u, x)
    return ans * (dellx / 3)


m0 = 140000
q = 2100
u = 2000
ti = 8
tf = 30
old_ans = 0

n = 5

print("Integration By Trapezoid")
for i in range(1, n + 1):
    new_ans = IntegrateTrapezoid(m0, q, u, ti, tf, i)
    print('n = ', i , ', res = ', new_ans, ', Error = ', RelativeApproxError(new_ans, old_ans))
    old_ans = new_ans
print('User Input = ', n , ' final ans = ' , new_ans)
print('------------------------------------------------------\n\n\n')



print("Integration by Simpson's 1 / 3 rule")
for i in range(1, n + 1):
    new_ans = IntegrateSimpsons13(m0, q, u, ti, tf, i * 2)
    print('n = ' , i , ', res = ', new_ans, ', Error = ', RelativeApproxError(new_ans, old_ans))
    old_ans = new_ans
print('User Input = ' , n , 'final ans = ' , new_ans)

print('\n\n')


print('Enter the value of n') 
n  = int(input()) 

new_ans = IntegrateTrapezoid(m0 , q , u, ti, tf ,n) 
print('Trapezoid Rule\nUser Input = ' , n , 'final ans = ' , new_ans)
new_ans = IntegrateSimpsons13(m0 ,q , u ,ti, tf, n)
print('Simpsons Rule\nUser Input = ' , n , 'final ans = ' , new_ans)