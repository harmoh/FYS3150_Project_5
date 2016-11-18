#ifndef LENNARDJONES_H
#define LENNARDJONES_H

class LennardJones
{
private:
    double m_epsilon = 1.0;
    double m_sigma = 1.0;
    double m_potentialEnergy = 0;

public:
    LennardJones();

    void calculateForces(class System &system);
    double potentialEnergy() const {return m_potentialEnergy;}

    double epsilon() const {return m_epsilon;}
    void setEpsilon(double epsilon) {m_epsilon = epsilon;}
    double sigma() const {return m_sigma;}
    void setSigma(double sigma) {m_sigma = sigma;}
};

#endif // LENNARDJONES_H
