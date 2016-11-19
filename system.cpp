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
    for(int i = 0; i < 100; i++)
    {
        Particle *particle = new Particle(UnitConverter::massFromSI(6.63352088e-26));
        double x = Random::nextDouble(0, 10); // random number in the interval [0,10]
        double y = Random::nextDouble(0, 10);
        double z = Random::nextDouble(0, 10);
        particle->position.set(x,y,z);
        particle->resetVelocityMaxwell(temp);
        m_particles.push_back(particle);
    }
    setSystemSize(vec3(10, 10, 10)); // Remember to set the correct system size!
}

// Apply periodic boundary conditions
void System::applyPBC()
{

}

void System::removeTotalMomentum()
{

}

void System::calculateForces()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    //m_angularMomentum.zeros();

    // Reset forces for all particles
    for(Particle *particle : m_particles)
    {
        particle->force.zeros();
    }
}

void System::step(double dt)
{
    m_integrator.integrate(*this, dt);
    m_steps++;
    m_time += dt;
}

int System::numberOfParticles() const
{
    return m_particles.size();
}

double System::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double System::kineticEnergy() const
{
    return m_kineticEnergy;
}

double System::potentialEnergy() const
{
    return m_potentialEnergy;
}

vec3 System::angularMomentum() const
{
    return m_angularMomentum;
}

void System::openFileAnimation(string filename)
{
    filename.append(".xyz");
    ofile_animation.open(filename);
    ofile_animation << setiosflags(ios::showpoint | ios::uppercase);
}

void System::writeToFileAnimation()
{
    ofile_animation << numberOfParticles() << endl;
    ofile_animation << "Comment line." << endl;
    for(Particle *particle : m_particles)
    {
        ofile_animation << particle->position.x() << " " << particle->position.y() << " " << particle->position.z() << "\n";
    }
}

std::vector<Particle *> &System::particles()
{
    return m_particles;
}
