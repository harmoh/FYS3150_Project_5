#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>
#include "vec3.h"

class Particle
{
public:
    vec3 position;
    vec3 velocity;
    vec3 acceleration;
    vec3 force;
    vec3 angularMomentum;
    double mass;

    Particle(vec3 position, vec3 velocity, double mass);
    Particle(double x, double y, double z, double vx, double vy, double vz, double mass);
    void resetForce();
};

#endif // PARTICLE_H
