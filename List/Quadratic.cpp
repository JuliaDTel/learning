#include "Quadratic.hpp"
#include <iostream>

Quadratic::Quadratic(double a1, double a2, double a3)
{
    if (a1 == 0) throw 0.5;
    a = a1;
    b = a2;
    c = a3;
}

Quadratic&Quadratic::operator = (const Quadratic &x)
{
    if (&x == this) return *this;
    a = x.a;
    b = x.b;
    c = x.c;
    return *this;
}

bool Quadratic:: operator <= (const Quadratic &x) const
{
    if (a>x.a) return false;
    if (b>x.b) return false;
    if (c>x.c) return false;
    return true;
}

ostream& operator << (ostream& out, const Quadratic &m)
{
    out << m.a << "x^2+" << m.b << "x+" << m.c;
    return out;
}
