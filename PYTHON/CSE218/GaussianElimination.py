import numpy as np

def GaussianElimination(A, B, d):
    rows = len(B)
    for i in range(0, rows):
        A[i].append(B[i])
    np.set_printoptions(precision=4)
    matrix = np.array(A)
    for i in range(0, rows - 1):
        for j in range(i + 1, rows):
            Arr = np.array(matrix[i])
            to_multiply = matrix[j][i] / Arr[i]
            Arr = Arr * to_multiply
            matrix[j] = Arr - matrix[j]
            if d == True:
                print(matrix)
                print('\n\n')

    Ans = np.arange(rows)
    Ans.dtype = 'f'

    for i in range(rows - 1, -1, -1):
        sum = 0
        for j in range(i + 1, rows):
            sum += matrix[i][j] * Ans[j]
        Ans[i] = (matrix[i][rows] - sum) / matrix[i][i]
    return Ans



rows = int(input())
cols = rows
A = []
for i in range(0, rows):
    arr = list(map(float, input().split()))
    A.append(arr)
    
input()

B = []
for i in range(0, rows):
    x = float(input())
    B.append(x)

Ans = Gauss(A, B, True)
print(flag)
if(flag == 1):
    print(Ans)
elif flag == 0:
    print('The System of Equations Has no solution')
else:
    print('The system has infinite solution\n')
    print(Ans)
''' 3
25 5 1
64 8 1
144 12 1

106.8
177.2
279.2
'''