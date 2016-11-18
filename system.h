#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <fstream>
#include <string>

class System
{
public:
    System();
    void calculateForcesAndEnergy();

    double t_final;
    long int totalSteps;

    int numberOfBodies() const;
    double totalEnergy() const;
    double kineticEnergy() const;
    double potentialEnergy() const;
    vec3 angularMomentum() const;
    void openFileAnimation(std::string filename);
    void writeToFileAnimation();

private:
    std::ofstream ofile_animation;

    vec3 m_angularMomentum;
    double m_kineticEnergy;
    double m_potentialEnergy;
};
#endif // SYSTEM_H
