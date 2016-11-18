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
    numberOfUnitCells = atoi(argv[1]); // Change number of unit cells
    tempInit = atoi(argv[2]); // Change initial temperature
    latticeConstant = atoi(argv[3]); // Change density (in Angstroms) of the lattice constant

    double dt = UnitConverter::timeFromSI(1e-15);

    System system;
    system.createFCCLattice(numberOfUnitCells, latticeConstant, tempInit);
    system.removeTotalMomentum();

    // Initial time
    clock_t time_initial = clock();

    Verlet integratorVerlet(dt);

    for(int step = 0; step < 10000; step++)
    {
        if(step % 100 == 0)
        {
            //solarSystem.writeToFilePlot();
        }
    }

    clock_t time_final = clock();

    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
