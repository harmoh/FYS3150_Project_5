#include "vec3.h"
#include "random.h"
#include <cmath>
#include <iostream>
using namespace std;

vec3::vec3()
{
    zeros();
}
vec3::vec3(double x, double y, double z)
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

void vec3::set(double x, double y, double z)
{
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

void vec3::randomGaussian(double min, double max)
{
    components[0] = Random::nextGaussian(min, max);
    components[1] = Random::nextGaussian(min, max);
    components[2] = Random::nextGaussian(min, max);
}

double vec3::lengthSquared()
{
    // Returns the square of the length (or norm) of the vector
    return components[0]*components[0]+components[1]*components[1]+components[2]*components[2];
}

double vec3::length()
{
    // Returns the length (or norm) of the vector
    return sqrt(lengthSquared());
}

vec3 vec3::cross(vec3 otherVector)
{
    return vec3(y()*otherVector.z() - z()*otherVector.y(),
                z()*otherVector.x() - x()*otherVector.z(),
                x()*otherVector.y() - y()*otherVector.x());
}

void vec3::print()
{
    cout << "[" << components[0] << ", " << components[1] << ", " << components[2] << "]" << endl;
}

void vec3::printName(string name)
{
    cout << name << ": ";
    print();
}

void vec3::zeros()
{
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

void vec3::max()
{
    components[0] = 1e10;
    components[1] = 1e10;
    components[2] = 1e10;
}

vec3 &vec3::operator+=(double rhs)
{
    components[0] += rhs;
    components[1] += rhs;
    components[2] += rhs;
    return *this;
}

vec3 &vec3::operator+=(vec3 rhs)
{
    components[0] += rhs[0];
    components[1] += rhs[1];
    components[2] += rhs[2];
    return *this;
}

vec3 &vec3::operator*=(double rhs)
{
    components[0] *= rhs;
    components[1] *= rhs;
    components[2] *= rhs;
    return *this;
}

vec3 &vec3::operator*=(vec3 rhs)
{
    components[0] *= rhs[0];
    components[1] *= rhs[1];
    components[2] *= rhs[2];
    return *this;
}

vec3 &vec3::operator-=(double rhs)
{
    components[0] -= rhs;
    components[1] -= rhs;
    components[2] -= rhs;
    return *this;
}

vec3 &vec3::operator-=(vec3 rhs)
{
    components[0] -= rhs[0];
    components[1] -= rhs[1];
    components[2] -= rhs[2];
    return *this;
}

vec3 &vec3::operator/=(double rhs)
{
    components[0] /= rhs;
    components[1] /= rhs;
    components[2] /= rhs;
    return *this;
}

vec3 &vec3::operator/=(vec3 rhs)
{
    components[0] /= rhs[0];
    components[1] /= rhs[1];
    components[2] /= rhs[2];
    return *this;
}

ostream &operator<<(ostream &os, const vec3 &myVector)
{
    os << "[" << myVector.x() << ", " << myVector.y() << ", " << myVector.z() << "]";
    return os;
}
