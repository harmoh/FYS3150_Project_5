# Runs main.cpp and plots the generated .txt files

import os
from math import *
import numpy as np
from matplotlib import pyplot as plt

os.system('c++ main.cpp io.cpp lennardjones.cpp particle.cpp statisticssampler.cpp system.cpp unitconverter.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')

def read(filename):
    infile = open(filename, 'r')
    # Read lines except for the first one:
    lines = infile.readlines()[-1]
    words = lines.split()
    x0 = float(words[5])*119.735 # Temperature
    x1 = float(words[4]) # Total energy
    infile.close()
    return x0, x1

x0 = []; x1 = [];

for temp in range (600, 800, 100):
    run = './main.o 5 ' + str(temp)
    os.system(run)
    # Fetching data by a call on read:
    x0_temp, x1_temp = read('Results/Statistics_' + str(temp) + 'K.txt')
    x0.append(str(0.5*temp));
    x1.append(x1_temp);

plt.xlabel('Temperature (K)')
plt.ylabel('Total energy')
plt.rcParams.update({'font.size': 10})
plt.plot(x0, x1)
plt.grid()
plt.savefig('TotalEnergy.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
#plt.show();
