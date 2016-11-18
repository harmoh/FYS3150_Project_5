#include "particle.h"
#include <cmath>

Particle::Particle(double mass) :
    m_mass(mass)
{

}

void Particle::resetForce()
{
    force.zeros();
}

void Particle::resetVelocityMaxwell(double temp)
{
    // Resetting the velocity according to a Maxwell-Boltzmann distribution
    double boltzmannConstant = 1.0;
    double standardDeviation = sqrt(boltzmannConstant * temp / m_mass);
    velocity.randomGaussian(0, standardDeviation);
}
