#include "particle.h"

Particle::Particle(double mass) :
    m_mass(mass)
{

}

void Particle::resetForce()
{
    force.zeros();
}
