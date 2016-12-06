#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "system.h"
#include "unitconverter.h"
#include "random.h"
#include "statisticssampler.h"

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
    int N = numberOfUnitCellsPerDimension;
    double b = latticeConstant;

    double unitCellX[4] = {0, 0.5, 0, 0.5};
    double unitCellY[4] = {0, 0.5, 0.5, 0};
    double unitCellZ[4] = {0, 0, 0.5, 0.5};

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                for(int atoms = 0; atoms < 4; atoms++)
                {
                    Particle *particle = new Particle(UnitConverter::massFromSI(6.63352088e-26));
                    double x = (unitCellX[atoms] + i) * b;
                    double y = (unitCellY[atoms] + j) * b;
                    double z = (unitCellZ[atoms] + k) * b;
                    particle->position.set(x, y, z);
                    particle->resetVelocityMaxwell(temp);
                    m_particles.push_back(particle);
                }
            }
        }
    }
    setSystemSize(vec3(N*b, N*b, N*b));
}

// Apply periodic boundary conditions
void System::applyPBC()
{
    double L = m_systemSize[0];
    for(double i = 0; i < m_particles.size(); i++)
    {
        Particle *particle = m_particles[i];
        for(int dim = 0; dim < 3; dim++) // In 3 dimensions
        {
            if(particle->position[dim] < 0) particle->position[dim] += L;
            if(particle->position[dim] >= L) particle->position[dim] -= L;
        }
    }
}

void System::removeTotalMomentum()
{
    StatisticsSampler sampler;
    vec3 momentum = sampler.sampleMomentum(*this);
    momentum /= m_particles.size();
    for(double i = 0; i < m_particles.size(); i++)
    {
        Particle *particle = m_particles[i];
        particle->velocity -= momentum / particle->mass();
    }
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
