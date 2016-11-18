#include "verlet.h"
#include "system.h"
#include "particle.h"

Verlet::Verlet()
{

}

void Verlet::integrate(System &system, double dt)
{
    system.calculateForces();

    for(Particle *particle : system.particles())
    {
        particle->acceleration = particle->force / particle->mass();
        particle->position += dt * particle->velocity + particle->acceleration * dt * dt / 2;

        system.calculateForces();
        particle->velocity += (particle->force / particle->mass() + particle->acceleration) * dt / 2;
    }
}
