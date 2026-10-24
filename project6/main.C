#include <iostream>
#include <cstring>
#include "Bigint.h"
using namespace std;

int main() {
    Bigint a(12345);
    Bigint b("98765432109876543210");
    Bigint c("2345");

    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;

    Bigint d = b;
    cout << "d(copy of b)=" << d << endl;
    Bigint e;
    e = a;
    cout << "e(assigned from a)=" << e << endl;

    cout << "--Comparisons--" << endl;
    cout << "a == e : " << (a == e) << endl;
    cout << "a <= e : " << (a <= e) << endl;
    cout << "a != b : " << (a != b) << endl;
    cout << "a <  b : " << (a <  b) << endl;
    cout << "a >= b : " << (a >= b) << endl;
     cout << "b >  a : " << (b > a)  << endl;
    cout << "c == a : " << (c == a) << endl;
    cout << "c <  a : " << (c < a)  << endl;

    return 0;
}
