#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;
int* oneRound ( int N );
int compScore ( int N , int M);
float game ();

int main() {
   float s = game ();
   cout << s << endl;
}

int compScore ( int N ,int M ){
    while ( M < 0 || M > 20){
        //cerr << "illegal ,input again\n";
        cin >> M;
    }
    int score = 0;
    if (M == N){
        score = 10;
    }
    else if (M<= N +1 && M >= N -1){
        score = 5;
    }
    else if (M <= N +3 && M >= N -3){
        score = 2;
    }
    else{
        score = 0;
    }
    return score;
}
    

int* oneRound ( int N ) {
    int M = 0;
    int* sc = new int [10];
    for (int i = 0 ; i < 10 ; i++){
        cin >> M;
        int score = compScore ( N , M );
        sc [i] = score;
    }
return sc;    
}

float game() {
    float s = 0.0;
    float sum1 = 0.0;
    int sum = 0;
    int N = 0;
    int** X;
    int count = 0 ,size = 10;
    //count为实际轮数
    X = new int* [size];
    while (true){
         int seed = 0;
        /*cout << "Please input a seed (input -1 to quit): \n";*/
        cin >> seed;

        if ( seed != -1 ){
            srand(seed);
            N = rand() % 21;
            //cout << N ;
        }
        else break;
        if ( count >= size) {
            int new_size = size*2;
            int** new_X = new int* [new_size];
            for ( int i = 0 ; i < size ; i++){
                new_X[i] = X[i];
            } 
            delete[] X;
            X = new_X;
            size = new_size; 
        }
        X[count++] = oneRound(N);
    }
    if (count == 0) return 0.0;//防止第一轮输-1出错

    for (int i = 0 ; i < count ; i++){
        for(int j = 0 ; j < 10 ; j++){
            sum += X[i][j];
        }
    }
    float ave = sum /(count*10.0);
    for (int i = 0 ; i < count ; i++){
        for(int j = 0 ; j < 10 ; j++){
            sum1 += pow(X[i][j]-ave , 2);
        }
    }
    s = sqrt( sum1 / (count*10.0) );
    delete[] X;
    return s;
}