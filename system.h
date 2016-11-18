#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include "vec3.h"
#include "particle.h"
#include "lennardjones.h"
#include "verlet.h"

class System
{
private:
    std::vector<Particle*> m_particles;

    LennardJones m_potential;
    Verlet m_integrator;

    std::ofstream ofile_animation;

    double m_steps = 0;
    double m_time = 0;

    vec3 m_systemSize;
    vec3 m_angularMomentum;
    double m_kineticEnergy;
    double m_potentialEnergy;

public:
    System();

    void createFCCLattice(int numberOfUnitCellsPerDimension, double latticeConstant, double temp);
    void applyPBC();
    void removeTotalMomentum();
    void calculateForces();
    void step(double dt);

    void openFileAnimation(std::string filename);
    void writeToFileAnimation();
    std::vector<Particle*> &particles();

    int numberOfParticles() const;
    double totalEnergy() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    vec3 angularMomentum() const;

    void setSystemSize(vec3 systemSize) {m_systemSize = systemSize;}
    vec3 systemSize() {return m_systemSize;}
    LennardJones &potential() {return m_potential;}
    Verlet &integrator() {return m_integrator;}
};
#endif // SYSTEM_H
