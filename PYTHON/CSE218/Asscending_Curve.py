import matplotlib.pyplot as plt
import math
import numpy as np
merge_x = []
merge_y = []
Quick_x = []
Quick_y = []
with open('C:/Users/Asus/Desktop/temp/Ascending CurveData for MergeSort.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break
        lst = line.split(' ')
        merge_x.append(float(lst[0]))
        merge_y.append(float(lst[1]))


with open('C:/Users/Asus/Desktop/temp/Ascending CurveData for QuickSort.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break
        lst = line.split(' ')
        Quick_x.append(float(lst[0]))
        Quick_y.append(float(lst[1]))


plt.plot(merge_x, merge_y, color = 'green' , linestyle = 'dashed', linewidth = '3',label = 'MergeSort')
#plt.plot(Quick_x, Quick_y, color = 'red' , linestyle = 'dashed', linewidth = '3',label = 'QuickSort')

plt.grid(True , which = 'both')
plt.xlabel('Size of array')
plt.title('Ascending')
plt.ylabel('Time(ms)')
plt.legend()
plt.show()
