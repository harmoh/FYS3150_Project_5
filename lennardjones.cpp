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

    double L = system.systemSize().x();

    double sigma6 = m_sigma * m_sigma * m_sigma * m_sigma * m_sigma * m_sigma;
    double sigma12 = sigma6 * sigma6;

    //double rijCut = 2.5 * m_sigma;
    //double rijCut2 = rijCut * rijCut;
    //double overRijCut2 = 1.0 / rijCut2;
    //double overRijCut6 = overRijCut2 * overRijCut2 * overRijCut2;
    //double overRijCut12 = overRijCut6 * overRijCut6;

    //double potentialEnergyAtRcut = 4 * m_epsilon * (sigma12 * overRijCut12 - sigma6 * overRijCut6);

    for (double i = 0; i < system.particles().size(); i++)
    {
        Particle *particle1 = system.particles()[i];
        double x = particle1->position.x();
        double y = particle1->position.y();
        double z = particle1->position.z();

        double fx = 0;
        double fy = 0;
        double fz = 0;

        double potentialEnergy = 0;

        for (double j = i + 1; j < system.particles().size(); j++)
        {
            Particle *particle2 = system.particles()[j];

            double dx = x - particle2->position.x();
            double dy = y - particle2->position.y();
            double dz = z - particle2->position.z();

            // Find the shortest distance (when dealing with period boundary conditions)
            if(dx > 0.5 * L) dx -= L;
            if(dx <= - 0.5 * L) dx += L;
            if(dy > 0.5 * L) dy -= L;
            if(dy <= - 0.5 * L) dy += L;
            if(dz > 0.5 * L) dz -= L;
            if(dz <= - 0.5 * L) dz += L;

            double rij2 = dx*dx + dy*dy + dz*dz;
            //if(rij2 < rijCut2)
            //{
                double overRij2 = 1.0 / rij2;
                double overRij = 1.0 / (sqrt(rij2));
                double overRij6 = overRij2 * overRij2 * overRij2;
                double overRij12 = overRij6 * overRij6;

                //double peGradient = 24 * m_epsilon * overRij2 * (2*sigma12*overRij12 - sigma6*overRij6);
                double peGradient = 24 * m_epsilon * (2*sigma12*overRij12*overRij - sigma6*overRij6*overRij);

                fx += peGradient * dx;
                fy += peGradient * dy;
                fz += peGradient * dz;

                particle2->force[0] -= peGradient * dx;
                particle2->force[1] -= peGradient * dy;
                particle2->force[2] -= peGradient * dz;

                potentialEnergy += 4 * m_epsilon * (sigma12*overRij12 - sigma6*overRij6);// - potentialEnergyAtRcut;
            //}
        }
        particle1->force[0] += fx;
        particle1->force[1] += fy;
        particle1->force[2] += fz;

        m_potentialEnergy += potentialEnergy;
    }
}
