#include "Ratio.hpp"
#include <iostream>

Ratio3::Ratio3(int a, int b, int c)
{
    x = a;
    y = b;
    z = c;
}

bool Ratio3::operator <= (const Ratio3 &n) const
{
    return (x*x + y*y + z*z) <= (n.x*n.x+n.y*n.y+n.z*n.z);
}

ostream& operator << (ostream &out, const Ratio3 &n)
{
    out << "(" << n.x << ", " << n.y << ", " << n.z << ")";
    return out;
}
