#ifndef _SET_HPP_
#define _SET_HPP_

#include <iosfwd>
#include <inttypes.h>
#include <cassert>
typedef uint32_t Base;
#define word(x) ((Base)(x/32))
#define bit(x) (x%32)

using namespace std;

class Set
{
private:
    Base *mas;
    size_t s;
    int maxel;
    void Add (int);
    void Del (int);
public:
    explicit Set (): mas(0), s(0), maxel(0) {}
    ~Set() {delete[] mas;}
    Set (const Set&);
    Set (int);
    bool operator () (int) const;
    Set& operator = (const Set &);
    Set& operator += (const Set &);
    Set operator + (const Set &) const;
    Set& operator -= (const Set &);
    Set operator - (const Set &) const;
    Set& operator *= (const Set &);
    Set operator * (const Set &) const;
    bool operator == (const Set &) const;
    bool operator < (const Set&) const;
    bool operator <= (const Set &) const;
    bool operator > (const Set &) const;
    bool operator >= (const Set &) const;
    friend ostream& operator << (ostream&, const Set&);
    friend bool ifempty (const Set &);
    friend int howmany(const Set &);
};

void test1 ();
void test2 ();
void test3 ();
void test4 ();
void test5 ();
void test6 ();
void test7 ();
void test8 ();
void test9 ();
void test10 ();
void test11 ();
void test12 ();

#endif // _SET_HPP_
