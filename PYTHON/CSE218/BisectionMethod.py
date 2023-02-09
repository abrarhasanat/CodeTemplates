import math
pi = math.acos(-1)
ans = 0


def f(h):
    return pi * h * h * (9 - h) - 12


def RelativeApproxError(Xnew, Xold):
    temp = (Xnew - Xold) / Xnew
    return abs(temp * 100)


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


bisect(0 , 1 , 0.5 , 20) 
print(ans)