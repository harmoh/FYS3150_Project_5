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

    int m_steps = 0;
    double m_time = 0;

    vec3 m_systemSize;

public:
    System();
    ~System();

    void createFCCLattice(int numberOfUnitCellsPerDimension, double latticeConstant, double temp);
    void applyPBC();
    void removeTotalMomentum();
    void calculateForces();
    void step(double dt);

    std::vector<Particle*> &particles();

    int numberOfParticles() const {return m_particles.size();}

    void setSystemSize(vec3 systemSize) {m_systemSize = systemSize;}
    double systemVolume() {return systemSize()[0] * systemSize()[1] * systemSize()[2];}
    vec3 systemSize() {return m_systemSize;}
    LennardJones &potential() {return m_potential;}
    Verlet &integrator() {return m_integrator;}

    int steps() {return m_steps;}
    void setSteps(int steps) {m_steps = steps;}
    double time() {return m_time;}
    void setTime(double time) {m_time = time;}
};
#endif // SYSTEM_H
