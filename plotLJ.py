# Plot Lennard-Jones potential

import numpy as np
from matplotlib import pyplot as plt

epsilon = 1;
sigma = 3.405;
r = np.linspace(0.1, 3*sigma, 1000);
potential = 4 * epsilon * ((sigma/r)**12 - (sigma/r)**6);

x = r/sigma;
y = potential/epsilon;

plt.xlabel('$r/\sigma$')
plt.ylabel('Potential $U(r)/\epsilon$')
plt.axis([0, 3, -1.2, 2])
plt.plot(x, y)
plt.grid()
plt.savefig('LJ_potential.eps', format = 'eps', dpi = 1000, bbox_inches='tight')
plt.show();
