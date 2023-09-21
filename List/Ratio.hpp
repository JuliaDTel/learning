#ifndef _RATIO_HPP_
#define _RATIO_HPP_

#include <iosfwd>
using namespace std;

class Ratio3
{
private:
    int x;
    int y;
    int z;
public:
    explicit Ratio3 (): x(0), y(0), z(0) {}
    Ratio3 (int, int, int);
    bool operator <= (const Ratio3 &) const;
    friend ostream& operator << (ostream &, const Ratio3 &);
};

#endif // _RATIO_HPP_
