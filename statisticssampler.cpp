#include "statisticssampler.h"
#include "system.h"
#include "lennardjones.h"
#include "unitconverter.h"
#include <iostream>
#include <iomanip>

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
    int width = 15;
    int precision = 6;
    if(!m_file.is_open())
    {
        m_file.open("Statistics.txt", ofstream::out);
        m_file << setw(width) << "Ek:";
        m_file << setw(width) << "Ep:";
        m_file << setw(width) << "Temp:";
        m_file << setw(width) << "Density:";
        m_file << setw(width) << "Momentum x:";
        m_file << setw(width) << "Momentum y:";
        m_file << setw(width) << "Momentum z:\n";
        m_file << setiosflags(ios::showpoint | ios::uppercase);
        if(!m_file.good())
        {
            cout << "Error! Could not open 'Statistics.txt'" << endl;
            exit(1);
        }
    }

    if(m_file.is_open())
    {
        m_file << setw(width) << setprecision(precision) << m_kineticEnergy;
        m_file << setw(width) << setprecision(precision) << m_potentialEnergy;
        m_file << setw(width) << setprecision(precision) << m_temperature;
        m_file << setw(width) << setprecision(precision) << m_density;
        m_file << setw(width) << setprecision(precision) << m_momentum[0];
        m_file << setw(width) << setprecision(precision) << m_momentum[1];
        m_file << setw(width) << setprecision(precision) << m_momentum[2] << "\n";
    }
}

void StatisticsSampler::sample(System &system)
{
    sampleKineticEnergy(system);
    samplePotentialEnergy(system);
    sampleTemperature(system);
    sampleDensity(system);
    sampleMomentum(system);
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
    for(double i = 0; i < system.particles().size(); i++)
    {
        Particle *particle = system.particles()[i];
        m_density += particle->mass();
    }
    m_density /= system.systemVolume();
}

vec3 StatisticsSampler::sampleMomentum(System &system)
{
    m_momentum.zeros();

    for(double i = 0; i < system.particles().size(); i++)
    {
        Particle *particle = system.particles()[i];
        vec3 momemtumTemp = particle->velocity * particle->mass();
        m_momentum += momemtumTemp;
    }
    return m_momentum;
}


