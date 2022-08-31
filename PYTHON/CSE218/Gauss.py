import numpy as np

EPS = 1e-9
flag = 1


def Gauss(a, b, d):
    global flag
    n = len(a)
    m = len(a[0])
    for i in range(0, n):
        a[i].append(b[i])

    Where = [-1] * m
    col = 0
    row = 0
    while col < m and row < n:
        sel = row
        for i in range(row, n):
            if abs(a[i][col]) > abs(a[sel][col]):
                sel = i
        if abs(a[sel][col]) < EPS:
            col += 1
            continue
        temp = a[sel]
        a[sel] = a[row]
        a[row] = temp
        Where[col] = row
        for i in range(0, n):
            if i != row:
                c = a[i][col] / a[row][col]
                for j in range(col, m + 1):
                    a[i][j] -= (a[row][j] * c)
        if(d):
            print(np.array(a))
            print('\n''\n')
        row += 1
        col += 1
    flag = 1
    ans = [0] * m
    for i in range(0, m):
        if Where[i] != -1:
            ans[i] = a[Where[i]][m] / a[Where[i]][i]
        else:
            flag = 2
    for i in range(i, n):
        sum = 0
        for j in range(0, m):
            sum += ans[j] * a[i][j]
        if(abs(sum - a[i][m]) > EPS):
            flag = 0
            break
    return ans


