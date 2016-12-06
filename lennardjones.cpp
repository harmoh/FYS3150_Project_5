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
    cout << "Time step: " << system.steps() << "\t";
    m_potentialEnergy = 0;
    double rij = 0;
    for(double i = 0; i < system.particles().size(); i++)
    {
        for(double j = i + 1; j < system.particles().size(); j++)
        {
            Particle *particle1 = system.particles()[i];
            Particle *particle2 = system.particles()[j];
            rij = fabs((particle1->position - particle2->position).length());
            if(rij > 0.5 * system.systemSize()[0])
            {
                //cout << "System size[0]: " << system.systemSize()[0] << "\n";
                //cout << "Rij before: " << rij << "\n";
                rij = fabs(rij - system.systemSize()[0]);
                //cout << "Rij after: " << rij << "\n";
            }

            m_potentialEnergy += 4 * m_epsilon * (pow((m_sigma / rij), 12) + pow((m_sigma / rij), 6));
        }
    }
    cout << "Potential energy = " << m_potentialEnergy << "\n";
}
