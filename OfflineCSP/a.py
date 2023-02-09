import sys 
arg_x = sys.argv[1] 
arg_y = sys.argv[2]

import matplotlib.pyplot as plt 

with open (arg_x) as fx , open(arg_y) as fy:
    x = [float(line.strip()) for line in fx]
    y = [float(line.strip()) for line in fy]


plt.plot(x, y)
plt.xlabel(arg_x[2:-4])
plt.ylabel(arg_y[2:-4])
plt.title(f"{arg_y[2:-4]} vs  {arg_x[2:-4]} graph") ;
name = f"{arg_y[2:-4]} vs {arg_x[:-4]}.png" ;
plt.show();
plt.savefig("name.png") ;
    