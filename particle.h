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

    Particle(double mass);
    void resetForce();

    double mass() {return m_mass;}
    void setMass(double mass) {m_mass = mass;}

private:
    double m_mass;

};

#endif // PARTICLE_H
