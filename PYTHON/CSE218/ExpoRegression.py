from typing import Match
import LinearRegressionNonOrigin
import math
def ExpoRegression(x , y):
    n = len(x) 
    for i in range(0 , n):
        y[i] = math.log(y[i])
    a0 , a1 = LinearRegressionNonOrigin.LinearRegression(x , y ) ;
    return math.exp(a0), a1 ;
