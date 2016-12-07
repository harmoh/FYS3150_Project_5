#include <iostream>
#include <cmath>
#include <time.h>
#include "vec3.h"
#include "verlet.h"
#include "unitconverter.h"
#include "system.h"
#include "io.h"
#include "statisticssampler.h"

using namespace std;
//ofstream ofile;

int main(int argc, char* argv[])
{
    int numberOfUnitCells = 5; // Unit cells in lattice
    double tempInit = UnitConverter::temperatureFromSI(300.0); // From K
    double latticeConstant = UnitConverter::lengthFromAngstroms(5.26); // From Angstroms

    // If there are input arguments are provided:
    // Change number of unit cells
    if(argc > 1) numberOfUnitCells = atoi(argv[1]);
    // Change initial temperature
    if(argc > 2) tempInit = UnitConverter::temperatureFromSI(atof(argv[2]));
    // Change density (in Angstroms) of the lattice constant
    if(argc > 3) latticeConstant = UnitConverter::lengthFromAngstroms(atof(argv[3]));

    // Set time step
    double dt = UnitConverter::timeFromSI(1e-15);

    System system;
    system.createFCCLattice(numberOfUnitCells, latticeConstant, tempInit);
    system.potential().setEpsilon(UnitConverter::temperatureFromSI(119.8));
    system.potential().setSigma(UnitConverter::lengthFromAngstroms(3.405));

    system.removeTotalMomentum();

    StatisticsSampler statisticsSampler;

    // Include temperature in outfile name, remove decimals
    string animationName = "Animation_";
    string str_temp = to_string(UnitConverter::temperatureToSI(tempInit));
    string tempInitStr = str_temp.substr(0, str_temp.find(".", 0));
    animationName.append(tempInitStr + "K.xyz");
    IO animation(animationName.c_str());

    // Initial time (CPU time)
    clock_t time_initial = clock();

    cout << "Particles: " << system.numberOfParticles() << "\tTemperature: " <<
            UnitConverter::temperatureToSI(tempInit) << endl;

    int totalSteps = 1000;
    for(int step = 0; step < totalSteps; step++)
    {
        system.step(dt);
        if(step % 10 == 0) statisticsSampler.sample(system, tempInit);
        animation.saveState(system);
    }
    animation.close();

    // Final time and time used (CPU time)
    clock_t time_final = clock();
    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
