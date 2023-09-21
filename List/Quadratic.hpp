#ifndef _QUADRATIC_HPP_
#define _QUADRATIC_HPP_

#include <iosfwd>

using namespace std;

class Quadratic
{
private: double a, b, c;
public:
    explicit Quadratic () : a(1), b(0), c(0) {}
    Quadratic(double, double, double);
    Quadratic & operator = (const Quadratic &x);
    bool operator <= (const Quadratic &) const;
    friend ostream& operator << (ostream &, const Quadratic &);
};

#endif
