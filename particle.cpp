#include "particle.h"

Particle::Particle(vec3 pos, vec3 vel, double mass_temp)
{
    position = pos;
    velocity = vel;
    mass = mass_temp;
}

Particle::Particle(double x, double y, double z, double vx, double vy, double vz, double mass_temp)
{
    position = vec3(x,y,z);
    velocity = vec3(vx,vy,vz);
    mass = mass_temp;
}

void Particle::resetForce()
{
    force.zeros();
}
