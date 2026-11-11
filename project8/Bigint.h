#ifndef _BIGINT_H_
#define _BIGINT_H_
#include <iostream>
using namespace std;

enum symbol {NEG = -1 , ZERO , POS};
class Bigint {
    char* s;
    size_t len;
    size_t size;
    symbol sym;
    bool isZero;
public:
    Bigint();
    Bigint(int t);
    Bigint(const Bigint& t);
    Bigint(const char* t);
    ~Bigint();
    Bigint& operator= (const Bigint& a);
    bool operator== (const Bigint& a);
    bool operator!= (const Bigint& a);
    bool operator< (const Bigint& a);
    bool operator<= (const Bigint& a);
    bool operator> (const Bigint& a);
    bool operator>= (const Bigint& a);
    Bigint operator+ (const Bigint& a);
    Bigint& operator+= (Bigint& a);
    Bigint operator* (const Bigint& a);
    Bigint& operator*= (Bigint& a);
    Bigint& operator-= ( Bigint& a);
    Bigint operator- ( Bigint& a);
    int abscmp(const Bigint& a);
    friend ostream& operator<<(ostream& os , const Bigint& a);
    friend Bigint absadd( Bigint& l,Bigint& r);
    friend Bigint abssub (Bigint& l , Bigint& r);
};

#endif
