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
        particle->position += particle->velocity * dt + particle->acceleration * dt * dt * 0.5;
    }
    system.applyPBC();
    system.calculateForces();
    for(Particle *particle : system.particles())
    {
        particle->velocity +=  dt * 0.5 * (particle->force / particle->mass() + particle->acceleration);
    }
}
