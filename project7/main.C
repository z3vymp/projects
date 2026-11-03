#include <iostream>
using namespace std;
#include "Bigint.h"

int main() {
    Bigint x1("9999999999");
    Bigint x2("1"); 
    cout << x1 << "+" << x2 << " = " << (x1 + x2) << endl;
    
    Bigint x3("2100000000"); 
    Bigint x4("2100000000");
    cout << x3 << "+" << x4 << " = " << (x3 += x4) << endl;
    
    Bigint y1(99);
    Bigint y2("99");        
    size_t v = 0;    
    Bigint y3(v);
    cout << y1 << "*" << y2 << " = " << (y1 * y2) << endl;    
    cout << y1 << "*" << y3 << " = " << (y1 * y3) << endl;
    
    Bigint y4("9999999999");
    Bigint y5("9999999999");
    cout << y4 << "*" << y5 << " = " << (y4 *= y5) << endl;
      
    return 0;
}