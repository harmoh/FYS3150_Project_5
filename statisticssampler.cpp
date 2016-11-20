#include "statisticssampler.h"
#include "system.h"
#include "lennardjones.h"
#include "unitconverter.h"
#include <iostream>

using namespace std;

StatisticsSampler::StatisticsSampler()
{

}

StatisticsSampler::~StatisticsSampler()
{
    if(m_file.is_open())
    {
        m_file.close();
    }
}

void StatisticsSampler::saveToFile(System &system)
{
    if(!m_file.is_open())
    {
        m_file.open("Statistics.txt", ofstream::out);
        m_file << "x: \ty: \tz:" << endl;
        if(!m_file.good())
        {
            cout << "Error! Could not open 'Statistics.txt'" << endl;
            exit(1);
        }
    }

    if(m_file.is_open())
    {
        Particle *particle = system.particles()[0];
        m_file << UnitConverter::lengthToAngstroms(particle->position.x()) << " ";
        m_file << UnitConverter::lengthToAngstroms(particle->position.y()) << " ";
        m_file << UnitConverter::lengthToAngstroms(particle->position.z()) << "\n";
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
