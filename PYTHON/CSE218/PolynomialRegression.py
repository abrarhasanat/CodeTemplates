import Gauss


def PolynomialRegression(x, y, m):
    #m<= (n - 2)
    n = len(x)
    a = []
    PowSum = [] 
    #powSum[i] = summation of x^i for all x
    for i in range(0, 2 * m + 1):
        sum = 0
        for j in range(0, n):
            sum += pow(x[j], i)
        PowSum.append(sum)
    for i in range(0, m + 1):
        temp = []
        for j in range(0, m + 1):
            temp.append(PowSum[i + j])
        a.append(temp)
    b = []
    for i in range(0, m + 1):
        sum = 0
        for j in range(0, n):
            sum += (pow(x[j], i) * y[j])
        b.append(sum)
    return Gauss.Gauss(a, b, False)

