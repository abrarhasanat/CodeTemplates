import matplotlib.pyplot as plt
import math
import numpy as np

merge_x = [0, 0.02, 0.04, 0.06, 0.08, 0.10, 0.12, 0.14, 0.16, 0.18,
           0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.36, 0.38]
merge_y = [18, 38, 75, 108, 124, 149, 177, 194, 210, 234,
           247, 263, 273, 282, 289, 300, 305, 309, 312, 318]
plt.plot(merge_x, merge_y, color='green', linestyle='dashed',
         linewidth='3', label='MergeSort')
#plt.plot(Quick_x, Quick_y, color = 'red' , linestyle = 'dashed', linewidth = '3',label = 'QuickSort')

plt.grid(True, which='both')
plt.xlabel('Field Current If')
plt.title('O.C.C curve')
plt.ylabel('No load Terminal voltage Eo')
plt.legend()
plt.show()
