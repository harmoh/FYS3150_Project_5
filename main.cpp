#include <iostream>
#include <cmath>
#include <time.h>
#include "vec3.h"
#include "verlet.h"

using namespace std;
ofstream ofile;

int main(int argc, char* argv[])
{
    int numberOfUnitCells = 5;
    double tempInit = 300; // K
    double latticeConstant = 5.26; // Angstrom

    numberOfUnitCells = atoi(argv[1]); // First command line argument
    tempInit = atoi(argv[2]); // Second command line argument
    latticeConstant = atoi(argv[3]); // Third command line argument

    solarSystem.totalSteps = 1e5;
    int t_initial = 0;

    // Final time is set differently for each method
    double dt = (solarSystem.t_final - t_initial) / (double) solarSystem.totalSteps;
    int skipPrint = 10; // Only print for every 10th step
    clock_t time_initial = clock();
    Verlet integratorVerlet(dt);
    solarSystem.openFilePlot("Positions");
    solarSystem.openFileAnimation("Positions");
    solarSystem.openFilePerihelion("PerihelionAngle");
    for(int step = 0; step < solarSystem.totalSteps; step++)
    {
        integratorVerlet.integrateOneStepVerlet(solarSystem);
        if(step % skipPrint == 0)
        {
            solarSystem.writeToFilePlot();
            //solarSystem.writeToFileAnimation();
        }
    }

    clock_t time_final = clock();

    double time_used = (time_final - time_initial) / (double) CLOCKS_PER_SEC;
    cout << "Time used: " << time_used << " seconds." << endl;

    return 0;
}
