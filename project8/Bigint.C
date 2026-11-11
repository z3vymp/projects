#include <iostream>
#include "Bigint.h"
#include <cstring>
using namespace std;

Bigint::Bigint(): len(1) , size(2){
    s = new char [size];
    s[0] = '0';
    s[1] = '\0';
    isZero = true;
    sym = ZERO;
}

Bigint::Bigint(int t):len(0){
    if ( t == 0 ) {
        len = 1;
        size = 2;
        s = new char [size];
        s[0] = '0';
        s[1] = '\0';
        isZero = true;
        sym = ZERO;
        return;
    }
    if ( t < 0) sym = NEG;
    else sym = POS;

    int a = abs(t);
    while (true) {
	len++;
	a = a/10;
	if (a == 0) break;
    }
    size = len+1;
    s = new char [size];
    s[(int)len] = '\0';
    for ( int i = 0 ; i < len ; i++ ) {
	s[len-1-i] = char(a%10+'0');
	a = a/10;
    }
    isZero = false;
}

Bigint::Bigint(const char* t):len(1), size(2), isZero(true) , sym(ZERO){
    if ( t == NULL || t[0] == '\0' || (t[0] == '0' && t[1] == '\0') ) {
        s = new char[2];
        s[0] = '0'; s[1] = '\0';
        sym = ZERO;
        return;
    }
    if ( t[0] != '-'){
        len = strlen(t);
        size = len + 1;
        s = new char [size];
        s[(int)len] = '\0';
        for ( int i = 0 ; i < len ; i++){
        s[i] = t[i];
        isZero = false;
        sym = POS;
        }
    }
    else{
        len = strlen(t) - 1;
        size = len + 1;
        s = new char [size];
        s[(int)len] = '\0';
        for ( int i = 0 ; i < len ; i++){
        s[i] = t[i+1];
        isZero = false;
        sym = NEG;
        }
    }
}

Bigint::~Bigint() {
    delete[] s;
}

Bigint::Bigint(const Bigint& t){
    sym = t.sym;
    isZero = t.isZero;
    len = t.len;
    size = t.size;
    s = new char [size];
    for ( int i = 0 ; i <= len ; i++){
        s[i] = t.s[i];
    }
}

ostream& operator<<(ostream& os , const Bigint& t){
    if (t.sym < 0){
        os << '-';
    }
    for(int i = 0 ; i < t.len ; i++){
   	    os << t.s[i];
    }
    return os;
}

int Bigint::abscmp(const Bigint& a){
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
    if ( sym != a.sym ) return false;
    int c = Bigint::abscmp(a);
    if (c == 0) return true;
    else return false;
}

bool Bigint::operator!=(const Bigint& a){
    if ( sym != a.sym ) return true;
    int c = Bigint::abscmp(a);
    if (c == 0) return false;
    else return true;
}

bool Bigint::operator<=(const Bigint& a){
    if (sym > a.sym) return false;
    if (sym < a.sym) return true;
    //同号
    int c = Bigint::abscmp(a);
    if ( sym < 0 ) {
        if (c < 0) return false;
        else return true;
    }
    else{
        if (c <= 0) return true;
        else return false;
    }
}

bool Bigint::operator<(const Bigint& a){
    if (sym > a.sym) return false;
    if (sym < a.sym) return true;
    int c = Bigint::abscmp(a);
    if ( sym > 0 ){
        if (c < 0) return true;
        else return false;
    }
    else {
        if ( c <= 0 ) return false;
        else return true;
    }
}

bool Bigint::operator>( const Bigint& a ){
    if (sym > a.sym) return true;
    if (sym < a.sym) return false;
    int c = Bigint::abscmp(a);
    if ( sym >= 0){
        if (c > 0) return true;
        else return false;
    }
    else {
        if ( c >= 0 ) return false;
        else return true;
    }
}

bool Bigint::operator>=( const Bigint& a ){
    if (sym > a.sym) return true;
    if (sym < a.sym) return false;
    int c = Bigint::abscmp(a);
    if ( sym >= 0 ){
        if (c >= 0) return true;
        else return false;
    }
    else {
        if ( c > 0 ) return false;
        else return true;
    }
}

Bigint& Bigint::operator=( const Bigint& a ){
    if (this == &a) return *this;
    sym = a.sym;
    size = a.size;
    len = a.len;
    isZero = a.isZero;
    char* p = new char[size];
    strcpy ( p , a.s );
    delete[] s;
    s = p;
    return *this;
}

Bigint absadd ( Bigint& l , Bigint& r ){//绝对值相加
    if (r.isZero) return l;
    if (l.isZero) {
        return r;
    }
    Bigint* longer;
    Bigint* shoter;
    if (r.len < l.len) {
        longer = &l;
        shoter = &r;
    }
    else {
        longer = &r;
        shoter = &l;
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
    delete[] l.s;
    l.s = temp;
    l.size = tempsize;
    l.len = tempsize-1;
    return l;
}


Bigint abssub (Bigint& l , Bigint& r){ //绝对值相减
    Bigint* longer;
    Bigint* shoter;
    if ( l.abscmp(r) >= 0 ){
        longer = &l;
        shoter = &r;
        if ( l.abscmp(r) == 0 ){
           delete[] l.s;
            l.len = 1;
            l.size = 2;
            l.s = new char[2];
            l.s[0] = '0';
            l.s[1] = '\0';
            l.isZero = true;
            l.sym = ZERO;
            return l;
        }
    } 
    else {
        longer = &r;
        shoter = &l;
    }
    int tempsize = longer->len + 1;
    char* temp = new char [tempsize];
    temp[tempsize-1] = '\0';
    int j = 0;//借位
    for (int i = 0 ; i < shoter->len ; i ++){
        if ( longer->s[ longer->len-1-i ] - j < shoter->s[ shoter->len-1-i ])  {
            j = 1;
            temp[tempsize-2-i] = longer->s[longer->len-1-i] + 10 - shoter->s[shoter->len-1-i] - j + '0';
        }
        else {
            temp[tempsize-2-i] = longer->s[longer->len-1-i] - shoter->s[shoter->len-1-i] - j + '0';
            j = 0;
        }
    }
    for (int i = 0 ; i < longer->len - shoter->len ; i++){
        if (longer->s[longer->len - shoter->len - 1 - i] - j < '0') {
            j = 1;
            temp[tempsize - 2 - shoter->len - i] = longer->s[longer->len - shoter->len - 1 - i] + 10 - j;
        }
        else
        temp [ tempsize - 2 - shoter->len - i ] = longer->s[longer->len - shoter->len - 1 - i] - j ;
        j = 0;   
    }
    while (temp[0] == '0' && tempsize > 1){
        char* new_temp = new char [tempsize-1];
        for(int i = 0 ; i < tempsize-1 ; i++ ){
            new_temp[i]=temp[i+1];
        }
        tempsize -= 1;
        delete[] temp;
        temp = new_temp;
    }    
    delete[] l.s;
    l.s = temp;
    l.size = tempsize;
    l.len = tempsize-1;
    return l;
}

Bigint& Bigint::operator-=( Bigint& a ){
    if ( a.isZero ) return *this;
    if ( isZero ) {
        *this = a;
        if (a.sym == POS) sym = NEG;
        else sym = POS;
        return *this; 
    }
    if ( sym > 0 && a.sym < 0 ) {
        absadd ( *this , a );
        sym = POS;
        return *this;
    }
    if ( sym < 0 && a.sym > 0 ) {
        absadd ( *this , a );
        sym = NEG;
        return *this;
    }
    if ( sym > 0 && a.sym > 0) {
        abssub( *this , a );
        return *this; 
    }
    else {
        if ( *this > a )sym = POS;
        else sym = NEG;
        abssub ( *this , a);
        return *this;
    }
}

Bigint Bigint::operator-( Bigint& a){
    Bigint c = *this;
    c -= a;
    return c;
}

Bigint& Bigint::operator+=( Bigint& a ){
    if (a.isZero) return *this;
    if ( isZero ) return *this = a;
    if (sym == a.sym){
        absadd(*this , a);
        return *this;
    }
    else {
        if ( abscmp(a) > 0 ){
            abssub ( *this , a );
            return *this;
        }
        if ( abscmp(a) < 0 ){
            abssub ( *this , a );
            sym = a.sym;
            return *this;
        }
        else {
            abssub ( *this , a );
            sym = ZERO;
            isZero = true;
            return *this;
        }
    }
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
        sym = ZERO;
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
    int thisSym = sym;
    int aSym = a.sym;

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
    if ( thisSym == aSym ) sym = POS;
    else sym = NEG;
    return *this;
}

Bigint Bigint::operator*(const Bigint& a){
    Bigint c = a;
    c *= *this;
    return c;
}
