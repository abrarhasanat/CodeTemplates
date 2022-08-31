from math import pow
N = 10001

b = [0 for i in range (0, N + 5)]
a = [0 for i in range (0, N + 5)]

for i in range (0, N, 1):
    b[i + 1] = b[i - b[i]] + 1

for i in range(0, N):
     a[i] = 1 + (i - 1 - (b[i] * (b[i] - 1)) // 2) * (2 ** b[i])
t = int(input())
for i in range (0, t):
    n = int(input())
    print(int(a[n]));