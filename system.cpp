#include "system.h"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

System::System()
{

}

void System::calculateForces()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    // Reset forces for all particles
    for(Particle &particle : m_particles)
    {
        particle.force.zeros();
    }

    double G = 4 * M_PI * M_PI;
    for(int i = 0; i < numberOfParticles(); i++)
    {
        Particle &particle1 = m_particles[i];
        for(int j = i+1; j < numberOfParticles(); j++)
        {
            Particle &particle2 = m_particles[j];
            vec3 deltaRVector = particle2.position - particle1.position;
            double dr = deltaRVector.length();
            double dr3 = dr*dr*dr;
            particle1.force += G * particle1.mass * particle2.mass * deltaRVector / (dr3);
            particle2.force -= G * particle1.mass * particle2.mass * deltaRVector / (dr3);

            m_angularMomentum += deltaRVector.cross(particle1.velocity);
        }
        m_potentialEnergy -= particle1.force.length() * particle1.position.length();
        m_kineticEnergy += 0.5 * particle1.mass * particle1.velocity.lengthSquared();
    }
}

int System::numberOfParticles() const
{
    return m_particles.size();
}

double System::totalEnergy() const
{
    return m_kineticEnergy + m_potentialEnergy;
}

double System::kineticEnergy() const
{
    return m_kineticEnergy;
}

double System::potentialEnergy() const
{
    return m_potentialEnergy;
}

vec3 System::angularMomentum() const
{
    return m_angularMomentum;
}


void System::openFileAnimation(string filename)
{
    filename.append(".xyz");
    ofile_animation.open(filename);
    ofile_animation << setiosflags(ios::showpoint | ios::uppercase);
}

void System::writeToFileAnimation()
{
    ofile_animation << numberOfParticles() << endl;
    ofile_animation << "Comment line." << endl;
    for(Particle &particle : m_particles)
    {
        ofile_animation << particle.position.x() << " " << particle.position.y() << " " << particle.position.z() << "\n";
    }
}

std::vector<Particle> &System::particles()
{
    return m_particles;
}
