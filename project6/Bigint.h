#ifndef _BIGINT_H_
#define _BIGINT_H_
#include <iostream>
using namespace std;

class Bigint {
    char* s;
    size_t len;
    size_t size;
    bool isZero;
public:
    Bigint();
    Bigint(size_t t);
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
    int cmp(const Bigint& a);
    friend ostream& operator<<(ostream& os , const Bigint& a);
};

#endif
