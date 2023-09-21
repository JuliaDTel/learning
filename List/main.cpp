#include "List1.hpp"
#include "Ratio.hpp"
#include "Quadratic.hpp"
#include <iostream>

using namespace std;

int main()
{
    try{
        Quadratic a(1, 1, 2);
        List1<Quadratic> b, n;
        b.Add(a);
        b = n;
        cout << n << endl;
        return 0;
    }
    catch (int n) {cout << "Don't try to read the base element of the list.";}
    catch (double t) {cout << "The first coefficient can't be 0.";}
    catch (bad_alloc e) {cout << "Can't allocate memory.";}
    catch (...) {cout << "Your circuit's dead, there's something wrong.";}
}
