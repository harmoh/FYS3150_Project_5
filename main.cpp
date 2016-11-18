#include <iostream>
#include <cmath>
#include <time.h>
#include "vec3.h"
#include "verlet.h"
#include "unitconverter.h"
#include "system.h"

using namespace std;
//ofstream ofile;

int main(int argc, char* argv[])
{
    int numberOfUnitCells = 5; // Density of initial lattice (in Angstroms)
    double tempInit = UnitConverter::temperatureFromSI(300.0); // From K
    double latticeConstant = UnitConverter::lengthFromAngstroms(5.26); // From Angstroms

    // If there are input arguments are provided:
    // Change number of unit cells
    if(argc > 2) numberOfUnitCells = atoi(argv[1]);
    // Change initial temperature
    if(argc > 3) tempInit = UnitConverter::temperatureFromSI(atof(argv[2]));
    // Change density (in Angstroms) of the lattice constant
    if(argc > 4) latticeConstant = UnitConverter::lengthFromAngstroms(atof(argv[3]));

    double dt = UnitConverter::timeFromSI(1e-15);

    System system;
    system.createFCCLattice(numberOfUnitCells, latticeConstant, tempInit);
    system.potential().setEpsilon(1.0);
    system.potential().setSigma(1.0);

    system.removeTotalMomentum();

    // Initial time
    clock_t time_initial = clock();

    cout << "Particles: " << system.numberOfParticles() << endl;
    for(int step = 0; step < 100; step++)
    {
        system.integrator().integrate(system, dt);
    }

    // Final time and time used
    clock_t time_final = clock();
    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
