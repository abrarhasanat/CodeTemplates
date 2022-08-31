def LinearRegression(x, y):
    n = len(x)
    SumX = 0
    SumY = 0
    SumXY = 0
    SumXsq = 0
    for i in range(0, n):
        SumX += x[i]
        SumY += y[i]
        SumXY += (x[i] * y[i])
        SumXsq += (x[i] * x[i])
    a1 = (n * SumXY - SumX * SumY) / (n * SumXsq - (SumX * SumX))
    a0 = (SumY / n)  - a1 * (SumX / n) 
    return (a0 , a1)
