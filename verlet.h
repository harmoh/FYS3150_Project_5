#ifndef VERLET_H
#define VERLET_H

class Verlet
{
public:
    Verlet();
    void integrate(class System &system, double dt);
};

#endif // VERLET_H
