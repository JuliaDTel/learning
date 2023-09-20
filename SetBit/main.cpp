#include "set.hpp"
#include <iostream>

using namespace std;

int main()
{
    try {
        test1 ();
        test2 ();
        test3();
        test4 ();
        test5 ();
        test6 ();
        test7 ();
        test8 ();
        test9 ();
        test10 ();
        test11 ();
        test12 ();
    }
    catch (int n) {cout << "Member of this set cannot be negative" << endl;}
    catch (...) {cout << "Your circuit's dead, there's something wrong" << endl;}
}

void test1 ()
{
    cout << "Test1" << endl;
    Set a(6), b(16);
    cout << b << "+=" << a << "=";
    b+=a;
    cout << b << endl;
    assert (b(6) && b(16));
    cout << "Success" << endl << endl;
}

void test2 ()
{
    cout << "Test2" << endl;
    Set a(6), b(16), c;
    c = a+b;
    cout << b << "+" << a << "=" << c << endl;
    assert (c(6) && c(16));
    cout << "Success" << endl << endl;
}

void test3()
{
    cout << "Test3" << endl;
    Set a(6), b(16), c(b);
    b+=a;
    cout << b << "-=" << a << "=";
    b-=a;
    cout << b << endl;
    assert (b == c);
    cout << "Success" << endl << endl;
}

void test4 ()
{
    cout << "Test4" << endl;
    Set a(6), b(16), c, d(b);
    b+=a;
    c = b-a;
    cout << b << "-" << a << "=" << c << endl;
    assert (c == d);
    cout << "Success" << endl << endl;
}

void test5()
{
    cout << "Test5" << endl;
    Set a(6), b(16);
    b+=a;
    cout << b << "*=" << a << "=";
    b*=a;
    cout << b << endl;
    assert (b == a);
    cout << "Success" << endl << endl;
}

void test6()
{
    cout << "Test6" << endl;
    Set a(6), b(16), c;
    b+=a;
    c = a*b;
    cout << b << "*" << a << "=" << c << endl;
    assert (c == a);
    cout << "Success" << endl << endl;
}

void test7()
{
    cout << "Test7" << endl;
    Set a(6), b(a);
    cout << a << "==" << b << endl;
    assert (a == b);
    cout << "Success" << endl << endl;
}

void test8 ()
{
    cout << "Test8  " << endl;
    Set b(16), a(6);
    b+=a;
    cout << a << "<" << b << endl;
    assert (a<b);
    cout << "Success" << endl << endl;
}

void test9 ()
{
    cout << "Test9" << endl;
    Set b(6), a(b);
    cout << a << "<=" << b << endl;
    assert (a<=b);
    cout << "Success" << endl << endl;
}

void test10 ()
{
    cout << "Test10  " << endl;
    Set b(16), a(6);
    b+=a;
    cout << b << ">" << a << endl;
    assert (b>a);
    cout << "Success" << endl << endl;
}

void test11 ()
{
    cout << "Test11  " << endl;
    Set b(6), a(b);
    cout << b << ">=" << a << endl;
    assert (b>=a);
    cout << "Success" << endl<<endl;
}

void test12 ()
{
    Set a(6), b;
    b = a;
    cout << "Test12  "<<endl;
    cout << b << "=" << a << endl;
    assert (b(6));
    cout << "Sussess" << endl<<endl;
}
