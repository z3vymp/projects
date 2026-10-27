#include <iostream>
using namespace std;

int* game() ;
int play(int) ;

int* game(){
    int count = 0 , size = 10 , N;
    int * s = new int [size];
    while (count < 100) {
        cin >> N;
        if (N < 0 || N > 20) continue;
        if (count >= size) {
            size *= 2;
            int * new_s = new int [size];
            for (int i = 0 ; i < count ; i++){
                new_s[i] = s[i];
                delete [] s;
                s = new_s;
            }
        }
        s[count++] = play(N);  
    }
return s;
}