#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <fstream>
#include <string>
#include <vector>
#include "vec3.h"
#include "particle.h"

class System
{
public:
    System();

    void applyPBC();
    void removeTotalMomentum();
    void createFCCLattice(int numberOfUnitCellsPerDimension, double latticeConstant, double temp);

    void calculateForces();

    void openFileAnimation(std::string filename);
    void writeToFileAnimation();
    std::vector<Particle> &particles();

    int numberOfParticles() const;
    double totalEnergy() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    vec3 angularMomentum() const;

    void setSystemSize(vec3 systemSize) {m_systemSize = systemSize;}
    vec3 systemSize() {return m_systemSize;}

private:
    std::vector<Particle> m_particles;
    std::ofstream ofile_animation;

    vec3 m_systemSize;
    vec3 m_angularMomentum;
    double m_kineticEnergy;
    double m_potentialEnergy;
};
#endif // SYSTEM_H
