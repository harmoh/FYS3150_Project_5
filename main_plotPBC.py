# Runs main.cpp and plots the generated .txt files

import os
from math import *
import numpy as np
from matplotlib import pyplot as plt

os.system('c++ main.cpp io.cpp lennardjones.cpp particle.cpp statisticssampler.cpp system.cpp unitconverter.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')
os.system('./main.o')

def read(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x0 = []; x1 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x0.append(float(words[0])) # x
        x1.append(float(words[1])) #y
    infile.close()
    return x0, x1

# Fetching data by a call on read_x_u_v for three different n:
x0, x1 = read('Statistics.txt')

plt.xlabel('x')
plt.ylabel('y')
plt.rcParams.update({'font.size': 10})
plt.plot(x0, x1, '.')
#plt.legend(loc='upper right',fancybox='True')
plt.grid()
plt.savefig('NotPBC.eps', format = 'eps', dpi = 1000, bbox_inches='tight') # Change to appropriate name
#plt.show();
