import math
from tabulate import tabulate
ans = 0
table_data = []


def f(x):
    if x == 1 or x == -2:
        return 0
    temp1 = (20 * x) / (1 - x)
    temp2 = math.sqrt(6 / (x + 2))
    return temp1 * temp2 - 1



def RelativeApproxError(Xnew, Xold):
    temp = (Xnew - Xold) / Xnew
    return abs(temp * 100)





#this Functions Update the soln of X in the Global variable  'ans '
def bisect(lower_bound, upper_bound, expected_approx_error, max_iteration_number):
    old_mid = 100 * 100
    for i in range(1, max_iteration_number + 1):
        new_mid = (lower_bound + upper_bound) / 2
        F_mid = f(new_mid)
        F_left = f(lower_bound)
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





#this functions collects Table data to show the absoulute relative approximate
#error upto 20 iteration
def BisectToTabulate(lower_bound, upper_bound, max_iteration_number):
    old_mid = 100 * 100
    for i in range(1, max_iteration_number + 1):
        new_mid = (lower_bound + upper_bound) / 2
        F_mid = f(new_mid)
        F_left = f(lower_bound)
        if F_mid * F_left < 0:
            upper_bound = new_mid
        else:
            lower_bound = new_mid
        tuple_row = (i, old_mid, new_mid,
                     RelativeApproxError(new_mid, old_mid))
        table_data.append(tuple_row)
        old_mid = new_mid








headers = ['iteration number  ', 'old ans  ',
           'new ans  ', 'abs relative aprrox error']

bisect(-0.2, 0.3, 0.5, 20)
BisectToTabulate(-0.2, 0.3, 20)
print('\n\n')

print('approximate answer by bisection method is ',  ans)

print('\n\n\n')
print('Table for showing absolute relative approx error after each iteration for 20 iteration')
print('\n')
print(tabulate(table_data, headers=headers))
