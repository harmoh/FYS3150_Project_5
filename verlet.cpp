#include "verlet.h"
#include "system.h"
#include "particle.h"

Verlet::Verlet(double dt) :
    m_dt(dt)
{

}

void Verlet::integrate(System &system)
{
    system.calculateForces();

    for(Particle &particle : system.particles())
    {
        particle.acceleration = particle.force / particle.mass;
        particle.position += m_dt * particle.velocity + particle.acceleration * m_dt * m_dt / 2;

        system.calculateForces();
        particle.velocity += (particle.force / particle.mass + particle.acceleration) * m_dt / 2;
    }
}
