# Runs main.cpp and plots the generated .txt files

import os
from math import *
import numpy as np
from matplotlib import pyplot as plt

os.system('c++ main.cpp io.cpp lennardjones.cpp particle.cpp statisticssampler.cpp system.cpp unitconverter.cpp vec3.cpp verlet.cpp -o main.o -O3 -std=c++11')

def read(filename):
    infile = open(filename, 'r')
    # Elements to be read in file:
    x0 = []; x1 = [];
    # Read lines except for the first one:
    lines = infile.readlines()[1:]
    for line in lines:
        words = line.split()
        x0.append(float(words[0])) # Step number
        x1.append(float(words[6])) # Temperature ratio
    infile.close()
    return x0, x1

# Temperature 50K
run = './main.o 5 50'
os.system(run)
# Fetching data by a call on read:
x0, x1_50 = read('Statistics_50K.txt')

# Temperature 100K
run = './main.o 5 100'
os.system(run)
# Fetching data by a call on read:
x0, x1_100 = read('Statistics_100K.txt')

# Temperature 150K
run = './main.o 5 150'
os.system(run)
# Fetching data by a call on read:
x0, x1_150 = read('Statistics_150K.txt')

# Temperature 200K
run = './main.o 5 200'
os.system(run)
# Fetching data by a call on read:
x0, x1_200 = read('Statistics_200K.txt')

# Temperature 250K
run = './main.o 5 250'
os.system(run)
# Fetching data by a call on read:
x0, x1_250 = read('Statistics_250K.txt')

# Temperature 300K
run = './main.o 5 300'
os.system(run)
# Fetching data by a call on read:
x0, x1_300 = read('Statistics_300K.txt')

# Temperature 400K
run = './main.o 5 400'
os.system(run)
# Fetching data by a call on read:
x0, x1_400 = read('Statistics_400K.txt')

# Temperature 500K
run = './main.o 5 500'
os.system(run)
# Fetching data by a call on read:
x0, x1_500 = read('Statistics_500K.txt')

# Temperature 600K
run = './main.o 5 600'
os.system(run)
# Fetching data by a call on read:
x0, x1_600 = read('Statistics_600K.txt')

# Temperature 700K
run = './main.o 5 700'
os.system(run)
# Fetching data by a call on read:
x0, x1_700 = read('Statistics_700K.txt')

# Temperature 800K
run = './main.o 5 800'
os.system(run)
# Fetching data by a call on read:
x0, x1_800 = read('Statistics_800K.txt')

plt.xlabel('Time step')
plt.ylabel('Temperature (K)')
plt.rcParams.update({'font.size': 10})
plt.plot(x0, x1_50, label = '$T = 50$')
plt.plot(x0, x1_100, label = '$T = 100$')
plt.plot(x0, x1_150, label = '$T = 150$')
plt.plot(x0, x1_200, label = '$T = 200$')
plt.plot(x0, x1_250, label = '$T = 250$')
plt.plot(x0, x1_300, label = '$T = 300$')
plt.plot(x0, x1_400, label = '$T = 400$')
plt.plot(x0, x1_500, label = '$T = 500$')
plt.plot(x0, x1_600, label = '$T = 600$')
plt.plot(x0, x1_700, label = '$T = 700$')
plt.plot(x0, x1_800, label = '$T = 800$')
plt.legend(loc='upper right',fancybox='True')
plt.grid()
plt.savefig('TemperatureRatio.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
#plt.show();
