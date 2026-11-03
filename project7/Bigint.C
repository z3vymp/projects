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

Bigint::Bigint(const char* t):len(1), size(2), isZero(true){
    if ( t == NULL ) {
        s = new char[2];
        s[0] = '0'; s[1] = '\0';
        return;
    }
        len = strlen(t);
        size = len + 1;
        s = new char [size];
        s[(int)len] = '\0';
        for ( int i = 0 ; i < len ; i++){
        s[i] = t[i];
        isZero = (len == 1 && s[0] == '0');
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
    isZero = a.isZero;
    char* p = new char[size];
    strcpy ( p , a.s );
    delete[] s;
    s = p;
    return *this;
}

Bigint& Bigint::operator+=( Bigint& a){
    if (a.isZero) return *this;
    if (isZero) {
        *this = a;
        return *this;
    }
    Bigint* longer;
    Bigint* shoter;
    if (a.len < len) {
        longer = this;
        shoter = &a;
    }
    else {
        longer = &a;
        shoter = this;
    }
    int tempsize = longer->len + 2;
    char* temp = new char[tempsize];
    temp[longer->len+1] = '\0';
    int j = 0;//进位
    for (int i = 0 ; i < shoter->len ; i++ ){
        int left = shoter->s[shoter->len-1-i] - '0';
        int right = longer->s[longer->len-1-i] - '0';
        int sum = left + right + j;
        temp[longer->len-i] = (sum%10) + '0'; 
        if (sum >= 10){
            j = 1;
        }
        else j = 0;
    }
    for (int i = 0 ; i < longer->len - shoter->len ; i++){
        int a = longer->s[longer->len - shoter->len - 1 - i] - '0';
        temp[longer->len - shoter->len - i] = (a + j)%10 + '0';
        if (a + j >= 10) j = 1;
        else j = 0 ;
    }
    if (j == 0) {
        tempsize -= 1;
        char* new_temp = new char [tempsize];
        for(int i = 0 ; i < tempsize ; i++ ){
            new_temp[i]=temp[i+1];
        }
        delete[] temp;
        temp = new_temp; 
    }
    else temp[0] = j + '0';
    delete[] s;
    s = temp;
    size = tempsize;
    len = tempsize-1;
    return *this;
}

Bigint Bigint::operator+(const Bigint& a){
    Bigint c = a;
    c += *this;
    return c;
}


Bigint& Bigint::operator*=(Bigint& a){
    if( isZero ) return *this;
    if( a.isZero ) {
        delete[] s;
        len = 1; size = 2;
        s = new char[2]; s[0] = '0'; s[1] = '\0';
        isZero = true;
        return *this;
    }
    Bigint* longer;
    Bigint* shoter;
    if (a.len < len) {
        longer = this;
        shoter = &a;
    }
    else {
        longer = &a;
        shoter = this;
    }

    int tempsize = a.len + len + 1;
    char* temp1 = new char [tempsize];
    for (int n = 0 ; n < tempsize ; n++){
        temp1[n] = '0';
    }
    temp1[tempsize-1] = '\0';
    int j = 0;//进位
    for( int m = 0 ; m < longer->len ; m++){
        int x = shoter->s[shoter->len-1] - '0';
        int y = longer->s[longer->len-1-m] - '0';
        int z = x * y;
        temp1[tempsize - 2 - m ] = (z+j)%10 +'0';
        j = (z+j)/10 ;
    }
    temp1[tempsize - 2 - longer->len] = j + '0';
    Bigint tempint1(temp1);
    delete[] temp1;

    for(int i = 1 ; i < shoter->len ; i++){
        
        int w = 0;//进位
        char* temp2 = new char [tempsize];
        for (int n = 0 ; n < tempsize ; n++){
            temp2[n] = '0';
        }
        temp2[tempsize-1] = '\0';
        for( int m = 0 ; m < longer->len ; m++){
                int x = shoter->s[shoter->len-1-i] - '0';
                int y = longer->s[longer->len-1-m] - '0';
                int z = x * y;
                temp2[tempsize - 2 - m - i] = (z+w)%10 +'0';
                w = (z+w)/10 ;
        }
        temp2[tempsize - 2 - longer->len -i] = w + '0';
        Bigint tempint2(temp2);
        delete[] temp2;
        tempint1 += tempint2;
    }
    *this = tempint1;
    if (s[0] == '0'){
        char* new_temp = new char [tempsize-1];
        for(int i = 0 ; i < tempsize-1 ; i++ ){
            new_temp[i]=s[i+1];
        }
        tempsize -= 1;
        delete[] s;
        s = new_temp;
        size = tempsize;
        len = tempsize - 1;
    }
    return *this;
}

Bigint Bigint::operator*(const Bigint& a){
    Bigint c = a;
    c *= *this;
    return c;
}
