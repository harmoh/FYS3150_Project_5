#include "statisticssampler.h"
#include "system.h"
#include "lennardjones.h"
#include <iostream>

using namespace std;

StatisticsSampler::StatisticsSampler()
{

}

void StatisticsSampler::saveToFile(System &system)
{
    if(!m_file.good())
    {
        m_file.open("Statistics.txt", ofstream::out);
        if(!m_file.good())
        {
            cout << "Error! Could not open 'Statistics.txt'" << endl;
            exit(1);
        }
    }
    if(m_file.is_open())
    {
        // Print values...
    }
}

void StatisticsSampler::sample(System &system)
{
    sampleKineticEnergy(system);
    samplePotentialEnergy(system);
    sampleTemperature(system);
    sampleDensity(system);
    saveToFile(system);
}

void StatisticsSampler::sampleKineticEnergy(System &system)
{
    m_kineticEnergy = 0;
    for(Particle *particle : system.particles())
    {
        // Get kinetic energy
    }
}

void StatisticsSampler::samplePotentialEnergy(System &system)
{
    m_potentialEnergy = system.potential().potentialEnergy();
}

void StatisticsSampler::sampleTemperature(System &system)
{

}

void StatisticsSampler::sampleDensity(System &system)
{

}
