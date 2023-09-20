#include "set.hpp"
#include <iostream>

Set::Set(int n)
{
    if (n<0) throw -1;
    mas = new Base [s = word(n) + 1];
    maxel = n;
    for (size_t i = 0; i<s; i++)
        mas[i] = 0;
    mas[word(n)] |= (1<<bit(n));
}

Set::Set (const Set& x)
{
    mas = new Base [s = x.s];
    for (size_t i = 0; i<s; i++)
        mas[i] = x.mas[i];
    maxel = x.maxel;
}

bool Set::operator () (int n) const
{
    if (s == 0) return false;
    return ((mas[word(n)] & (1<<bit(n))) != 0);
}

Set&Set::operator=(const Set&x)
{
    if (&x == this) return *this;
    Base *p = new Base [s = x.s];
    for (size_t i = 0; i<s; i++)
        p[i] = x.mas[i];
    delete []mas;
    mas = p;
    maxel = x.maxel;
    return *this;
}

void Set::Add(int n)
{
    if (n < 0) throw -1;
    if ((word(n) + 1) > (Base)s)
    {
        Base* p = new Base [word(n) + 1];
        for (size_t i = 0; i<s; i++)
            p[i] = mas[i];
        for (size_t i = s; i<(s = word(n)+1); i++)
            p[i] = 0;
        delete[] mas;
        mas = p;
    }
    mas[word(n)] |= (1<<bit(n));
    if (n > maxel) maxel = n;
}

void Set::Del(int n)
{
    mas[word(n)] &= ~(1<<bit(n));
}

bool Set::operator==(const Set& x) const
{
    if (s != x.s) return false;
    for (size_t i = 0; i<s; i++)
        if (mas[i] != x.mas[i]) return false;
    return true;
}

bool Set::operator< (const Set& x) const
{
    if ((x.s < s)||(*this == x)) return false;
    Set rez(*this);
    for (int i = 0; i < maxel; i++)
    {
        if (rez(i) & !x(i)) return false;
    }
    return true;
}

bool Set::operator <= (const Set &x) const
{
    return ((*this<x) || (*this == x));
}

bool Set::operator > (const Set &x) const
{
    return (x<*this);
}

bool Set::operator >= (const Set &x) const
{
    return (x<=*this);
}

Set&Set::operator+=(const Set& x)
{
    Set rez(*this);
    for (int i = 0; i<=x.maxel; i++)
        if ((!rez(i))&(x(i))){Add(i);};
    return *this;
}

Set Set::operator+(const Set& x) const
{
    Set rez(*this);
    rez+=x;
    return rez;
}

Set&Set::operator-=(const Set &x)
{
    Set rez(*this);
    for (int i = 0; i<= x.maxel; i++)
    if ((rez(i))&(x(i))) {Del(i);};
    return *this;
}

Set Set::operator- (const Set &x) const
{
    Set rez(*this);
    rez-=x;
    return rez;
}

Set&Set::operator*=(const Set &x)
{
    Set rez(*this);
    rez = rez*x;
    *this = rez;
    return *this;
}

Set Set::operator * (const Set &x) const
{
    Set rez(*this);
    rez -= (rez - x);
    return rez;
}

int howmany(const Set &x)
{
    int t = 0;
    for (int i = 0; i<=x.maxel; i++)
        if (x(i)) t++;
    return t;
}

bool ifempty (const Set &x)
{
    return !(bool)(howmany(x));
}

ostream& operator << (ostream& out, const Set& x)
{
    bool f = true;
    out << "(";
    if (x.s)
        for (int i = 0; i<=x.maxel; i++)
            if (x(i)) {out << (f ? "" : ", ") << i; f = false;}
    out << ")";
    return out;
}
