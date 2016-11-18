#include "system.h"

System::System()
{

}

void System::calculateForces()
{
    m_kineticEnergy = 0;
    m_potentialEnergy = 0;
    m_angularMomentum.zeros();

    // Reset forces for all bodies
    for(CelestialBody &body : m_bodies)
    {
        body.force.zeros();
    }

    double G = 4 * M_PI * M_PI;
    for(int i = 0; i < numberOfBodies(); i++)
    {
        CelestialBody &body1 = m_bodies[i];
        for(int j = i+1; j < numberOfBodies(); j++)
        {
            CelestialBody &body2 = m_bodies[j];
            vec3 deltaRVector = body2.position - body1.position;
            double dr = deltaRVector.length();
            double dr3 = dr*dr*dr;
            body1.force += G * body1.mass * body2.mass * deltaRVector / (dr3);
            body2.force -= G * body1.mass * body2.mass * deltaRVector / (dr3);

            m_angularMomentum += deltaRVector.cross(body1.velocity);
        }
        m_potentialEnergy -= body1.force.length() * body1.position.length();
        m_kineticEnergy += 0.5 * body1.mass * body1.velocity.lengthSquared();
    }
}

int System::numberOfBodies() const
{
    return m_bodies.size();
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
    ofile_plot << setiosflags(ios::showpoint | ios::uppercase);
}

void System::writeToFileAnimation()
{
    ofile_animation << numberOfBodies() << endl;
    ofile_animation << "Comment line." << endl;
    for(CelestialBody &body : m_bodies)
    {
        ofile_animation << body.position.x() << " " << body.position.y() << " " << body.position.z() << "\n";
    }
}
