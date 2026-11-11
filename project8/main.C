#include <iostream>
using namespace std;
#include "Bigint.h"


int main() {
Bigint a("12345678901234567890"); 
Bigint b("-98765432109876543210");
Bigint c("5555555555");
Bigint d("-1");
Bigint zero(0);
Bigint x;
x = a;
cout << x << " == " << a << "?  " << (x == a) << endl;
cout << x << " != " << b << "?  " << (x != b) << endl;
cout << a << " > "  << b << "?  " << (a > b)<< endl;
cout << a << " <= " << c << "?  " << (a <= c) << endl;
cout << b << " < "  << zero << "?  " << (b < zero) << endl;
cout << zero << " >= " << d << "?  " << (zero >= d) << endl << endl;
cout << a << " + " << c << " = " << (a + c) << endl;
cout << a << " + " << b << " = " << (a + b) << endl;
cout << b << " + " << zero << " = " << (b + zero) << endl;
cout << b << " + " << b << " = " << (b + b) << endl << endl;
std::cout << a << " - " << c << " = " << (a - c) << std::endl;
std::cout << c << " - " << a << " = " << (c - a) << std::endl;
std::cout << zero << " - " << a << " = " << (zero - a) << std::endl;
std::cout << a << " - " << b << " = " << (a - b) << std::endl << std::endl;
std::cout << a << " * " << c << " = " << (a * c) << std::endl;
std::cout << b << " * " << b << " = " << (b * b) << std::endl;
std::cout << a << " * " << zero << " = " << (a * zero) << std::endl << std::endl;
std::cout << "(" << a << " + " << b << "-" << c << ") * " << d << " = " << (a + b-c) * d << std::endl;
return 0;
}
