
def cal(val, x, avoid):
    mul = 1
    for i in x:
        if(i == avoid):
            continue
        mul *= (val - i)
    return mul


n = int(input())
x = []
y = []
for i in range(n):
    tmp = float(input())
    x.append(tmp)
for i in range(n):
    tmp = float(input())
    y.append(tmp)

x1 = float(input())
ans = 0
for i in range(0, n):
    up = cal(x1, x, x[i])
    down = cal(x[i], x, x[i])
    ans += (up / down)  * (y[i]) 
print(ans)
