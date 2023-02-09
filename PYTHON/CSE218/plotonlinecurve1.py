import math
import numpy as np
import matplotlib.pyplot as plt
pi = math.acos(-1)
ans = 0


def f(h):
    return pi * h * h * (9 - h) - 12

x_data = np.arange(-1, 10, 0.00005)
y_data = []
for i in x_data:
    if i == 1:
        continue
    y_data.append(f(i))
plt.plot(x_data, y_data)
plt.xlabel("Mole Fraction x")
plt.ylabel("F(x) =  (x/(1-x) *√(2pt/(2+x))) / k - 1")
plt.ylim(- 30, 1000)
plt.plot([-1, 10], [0, 0])
plt.show()