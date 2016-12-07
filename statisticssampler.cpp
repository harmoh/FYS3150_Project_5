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

void StatisticsSampler::saveToFile(System &system, double tempInit)
{
    // Include temperature in outfile name, remove decimals
    string fileName = "Statistics_";
    string str_temp = to_string(UnitConverter::temperatureToSI(tempInit));
    string tempInitStr = str_temp.substr(0, str_temp.find(".", 0));
    fileName.append(tempInitStr + "K.txt");

    int width = 15;
    int precision = 6;
    if(!m_file.is_open())
    {
        m_file.open(fileName, ofstream::out);
        m_file << setw(width) << "Time step:";
        m_file << setw(width) << "Time:";
        m_file << setw(width) << "Ek:";
        m_file << setw(width) << "Ep:";
        m_file << setw(width) << "Temp:";
        m_file << setw(width) << "T/Ti:";
        m_file << setw(width) << "Density:";
        //m_file << setw(width) << "Momentum x:";
        //m_file << setw(width) << "Momentum y:";
        //m_file << setw(width) << "Momentum z:";
        m_file << "\n";
        m_file << setiosflags(ios::showpoint | ios::uppercase);
        if(!m_file.good())
        {
            cout << "Error! Could not open 'Statistics.txt'" << endl;
            exit(1);
        }
    }

    if(m_file.is_open())
    {
        m_file << setw(width) << setprecision(precision) << system.steps();
        m_file << setw(width) << setprecision(precision) << system.time();
        m_file << setw(width) << setprecision(precision) << m_kineticEnergy;
        m_file << setw(width) << setprecision(precision) << m_potentialEnergy;
        m_file << setw(width) << setprecision(precision) << m_temperature;
        m_file << setw(width) << setprecision(precision) << m_temperature/tempInit;
        m_file << setw(width) << setprecision(precision) << m_density;
        //m_file << setw(width) << setprecision(precision) << m_momentum[0];
        //m_file << setw(width) << setprecision(precision) << m_momentum[1];
        //m_file << setw(width) << setprecision(precision) << m_momentum[2];
        m_file << "\n";
    }
}

void StatisticsSampler::sample(System &system, double tempInit)
{
    sampleKineticEnergy(system);
    samplePotentialEnergy(system);
    sampleTemperature(system);
    sampleDensity(system);
    sampleMomentum(system);
    saveToFile(system, tempInit);
}

void StatisticsSampler::sampleKineticEnergy(System &system)
{
    m_kineticEnergy = 0;
    for(Particle *particle : system.particles())
    {
        m_kineticEnergy += 0.5 * particle->mass() * particle->velocity.lengthSquared();
    }
}

void StatisticsSampler::samplePotentialEnergy(System &system)
{
    m_potentialEnergy = system.potential().potentialEnergy();
}

void StatisticsSampler::sampleTemperature(System &system)
{
    m_temperature = 2.0/3 * m_kineticEnergy / (system.particles().size());
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


