import matplotlib.pyplot as plt
import math
import numpy as np

x_data = [0	,5	,9	,12	,19	,22	, 25 ,26	,28	,30	,33	,40	] ;
y_data = [1011,1255,1347,1101,1203,1245,1394.69,1378,1315,1475,1547,1689]
plt.plot(x_data, y_data)
plt.xlabel("time(sec)")
plt.ylabel("mass (metric ton)")
plt.plot([25 , 25] , [0 , 1700])
plt.show();