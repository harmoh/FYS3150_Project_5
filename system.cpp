#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "system.h"
#include "unitconverter.h"
#include "random.h"

using namespace std;

System::System()
{

}

System::~System()
{
    for(Particle *particle : particles())
    {
        delete particle;
    }
    m_particles.clear();
}

void System::createFCCLattice(int numberOfUnitCellsPerDimension, double latticeConstant, double temp)
{
    int L = 10; // Lattice size
    for(int i = 0; i < 100; i++)
    {
        Particle *particle = new Particle(UnitConverter::massFromSI(6.63352088e-26));
        double x = Random::nextDouble(0, L); // random number in the interval [0,10]
        double y = Random::nextDouble(0, L);
        double z = Random::nextDouble(0, L);
        particle->position.set(x,y,z);
        particle->resetVelocityMaxwell(temp);
        m_particles.push_back(particle);
    }
    // Remember to set the correct system size!
    setSystemSize(vec3(L, L, L));
}

// Apply periodic boundary conditions
void System::applyPBC()
{
    for(int i = 0; i < m_particles.size(); i++)
    {
        Particle *particle = m_particles[i];
        for(int dim = 0; dim < 3; dim++) // In 3 dimensions
        {
            if(particle->position[dim] < 0) particle->position[dim] += m_systemSize[dim];
            if(particle->position[dim] >= m_systemSize[dim]) particle->position[dim] -= m_systemSize[dim];
        }
    }
}

void System::removeTotalMomentum()
{

}

void System::calculateForces()
{
    // Reset forces for all particles
    for(Particle *particle : m_particles)
    {
        particle->resetForce();
    }
    m_potential.calculateForces(*this);
}

void System::step(double dt)
{
    m_integrator.integrate(*this, dt);
    m_steps++;
    m_time += dt;
}

std::vector<Particle *> &System::particles()
{
    return m_particles;
}
