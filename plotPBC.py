# Runs main.cpp and plots the generated .txt files

# NOTE: This script will only work if the two first columns of the Statistics
# file is changed to the position of one atom in x and y dimension, respectively.

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
        x1.append(float(words[1])) # y
    infile.close()
    return x0, x1

# Fetching data by a call on read:
x0, x1 = read('Results/Statistics_300K.txt')

plt.xlabel('x')
plt.ylabel('y')
plt.rcParams.update({'font.size': 10})
plt.plot(x0, x1, '.')
plt.grid()
plt.savefig('NotPBC.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
