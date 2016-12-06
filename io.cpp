#include "io.h"
#include "system.h"
#include "particle.h"
#include "unitconverter.h"
#include <cstdlib>

using namespace std;

IO::IO(const char *filename)
{
    open(filename);
}

IO::~IO()
{
    file.close();
}

void IO::open(const char *filename)
{
    if(!file.is_open())
    {
        file.open(filename);
    }
    else
    {
        cout << "Error! " << filename << " is already open." << endl;
        exit(1);
    }
}

void IO::close()
{
    if(file.is_open()) file.close();
}

void IO::saveState(System &system)
{
    if(file.is_open())
    {
        file << system.numberOfParticles() << "\n";
        file << "Comment line. Time step: " << system.steps() << "\n";
        for(Particle *particle : system.particles())
        {
            file << "H "; // Particle type, can be used in Ovito to set default size and color
            file << UnitConverter::lengthToAngstroms(particle->position.x()) << " ";
            file << UnitConverter::lengthToAngstroms(particle->position.y()) << " ";
            file << UnitConverter::lengthToAngstroms(particle->position.z()) << "\n";
        }
    }
}
