#ifndef VERLET_H
#define VERLET_H

class Verlet
{
public:
    double m_dt;
    Verlet(double dt);
    void integrate(class System &system);
};

#endif // VERLET_H
