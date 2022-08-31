def LinearRegressionOrigin(x ,y):
    n = len(x)
    SumXY = 0 
    SumXsq = 0
    for i in range(0 , n):
        SumXY += (x[i] * y[i])
        SumXsq += (x[i] * x[i])
    return SumXY / SumXsq 