#include "lennardjones.h"
#include "system.h"
#include "vec3.h"
#include <cmath>
#include <iostream>

using namespace std;

LennardJones::LennardJones()
{

}

void LennardJones::calculateForces(System &system)
{
    m_potentialEnergy = 0;

    double L = system.systemSize()[0];

    double sigma6 = m_sigma * m_sigma * m_sigma * m_sigma * m_sigma * m_sigma;
    double sigma12 = sigma6 * sigma6;

    double rc = 2.5 * m_sigma;
    double rc2 = rc * rc;
    double overRc2 = 1.0 / rc2;
    double overRc6 = overRc2 * overRc2 * overRc2;
    double overRc12 = overRc6 * overRc6;

    double potentialEnergyRc = 4 * m_epsilon * (sigma12 * overRc12 - sigma6 * overRc6);

    for (double i = 0; i < system.particles().size(); i++)
    {
        Particle *particle1 = system.particles()[i];
        double x = particle1->position[0];
        double y = particle1->position[1];
        double z = particle1->position[2];

        double fx = 0;
        double fy = 0;
        double fz = 0;

        double potentialEnergy = 0;

        for (double j = i + 1; j < system.particles().size(); j++)
        {
            Particle *particle2 = system.particles()[j];

            double dx = x - particle2->position[0];
            double dy = y - particle2->position[1];
            double dz = z - particle2->position[2];

            // Find the shortest distance (when dealing with period boundary conditions)
            if(dx > 0.5 * L) dx -= L;
            if(dx <= - 0.5 * L) dx += L;
            if(dy > 0.5 * L) dy -= L;
            if(dy <= - 0.5 * L) dy += L;
            if(dz > 0.5 * L) dz -= L;
            if(dz <= - 0.5 * L) dz += L;

            double rij2 = dx*dx + dy*dy + dz*dz;
            if(rij2 < rc2)
            {
                double overRij2 = 1.0 / rij2;
                double overRij6 = overRij2 * overRij2 * overRij2;
                double overRij12 = overRij6 * overRij6;

                double forceGradient = 24 * m_epsilon * overRij2 * (2*sigma12*overRij12 - sigma6*overRij6);

                fx += forceGradient * dx;
                fy += forceGradient * dy;
                fz += forceGradient * dz;

                particle2->force[0] -= forceGradient * dx;
                particle2->force[1] -= forceGradient * dy;
                particle2->force[2] -= forceGradient * dz;

                potentialEnergy += 4 * m_epsilon * (sigma12*overRij12 - sigma6*overRij6) - potentialEnergyRc;
            }
        }
        particle1->force[0] += fx;
        particle1->force[1] += fy;
        particle1->force[2] += fz;

        m_potentialEnergy += potentialEnergy;
    }
}
