#include "verlet.h"
#include "system.h"
#include "particle.h"

Verlet::Verlet()
{

}

void Verlet::integrate(System &system, double dt)
{
    if(m_firstStep)
    {
        system.calculateForces();
        m_firstStep = false;
    }

    for(Particle *particle : system.particles())
    {
        particle->acceleration = particle->force / particle->mass();
        particle->position += dt * particle->velocity + particle->acceleration * dt * dt / 2;
    }
    system.applyPBC();
    system.calculateForces();
    for(Particle *particle : system.particles())
    {
        particle->velocity += (particle->force / particle->mass() + particle->acceleration) * dt / 2;
    }
}
