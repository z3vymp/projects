#include <iostream>
#include "Bigint.h"
#include <cstring>
using namespace std;

Bigint::Bigint(): len(1) , size(2){
    s = new char [size];
    s[0] = '0';
    s[1] = '\0';
    isZero = true;
}

Bigint::Bigint(size_t t):len(0){
    if ( t == 0 ) {
        len = 1;
        size = 2;
        s = new char [size];
        s[0] = '0';
        s[1] = '\0';
        isZero = true;
        return;
    }
    size_t a = t;
    while (true) {
	len++;
	a = a/10;
	if (a == 0) break;
    }
    size = len+1;
    s = new char [size];
    s[(int)len] = '\0';
    for ( int i = 0 ; i < len ; i++ ) {
	s[(int)len-1-i] = char(t%10+'0');
	t = t/10;
    }
    isZero = false;
}

Bigint::Bigint(const char* t){
    if ( t != NULL){
        len = strlen(t);
        size = len + 1;
        s = new char [size];
        s[(int)len] = '\0';
        for ( int i = 0 ; i < len ; i++){
        s[i] = t[i];
        isZero = (len == 1 && s[0] == '0');
        }
    }
}

Bigint::~Bigint() {
    delete[] s;
}

Bigint::Bigint(const Bigint& t){
    isZero = t.isZero;
    len = t.len;
    size = t.size;
    s = new char [size];
    for ( int i = 0 ; i <= len ; i++){
        s[i] = t.s[i];
    }
}

ostream& operator<<(ostream& os , const Bigint& t){
    for(int i = 0 ; i < t.len ; i++){
   	    os << t.s[i];
    }
    return os;
}

int Bigint::cmp(const Bigint& a){
    if (len < a.len) return -1;
    if (len > a.len) return 1;
    for (int i = 0 ; i < len ; i++){
        if ( s[i] < a.s[i] ) {
            return -1;
        }
        else if ( s[i] > a.s[i] ) {
            return 1;
        }
    }
    return 0;
}

bool Bigint::operator==(const Bigint& a){
    int c = Bigint::cmp(a);
    if (c == 0) return true;
    else return false;
}

bool Bigint::operator!=(const Bigint& a){
    int c = Bigint::cmp(a);
    if (c == 0) return false;
    else return true;
}

bool Bigint::operator<=(const Bigint& a){
    int c = Bigint::cmp(a);
    if (c <= 0) return true;
    else return false;
}

bool Bigint::operator<(const Bigint& a){
    int c = Bigint::cmp(a);
    if (c < 0) return true;
    else return false;
}

bool Bigint::operator>( const Bigint& a ){
    int c = Bigint::cmp(a);
    if (c > 0) return true;
    else return false;
}

bool Bigint::operator>=( const Bigint& a ){
    int c = Bigint::cmp(a);
    if (c >= 0) return true;
    else return false;
}

Bigint& Bigint::operator=( const Bigint& a ){
    if (this == &a) return *this;
    size = a.size;
    len = a.len;
    char* p = new char[size];
    strcpy ( p , a.s );
    delete[] s;
    s = p;
    return *this;
}
