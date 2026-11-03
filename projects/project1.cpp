#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    while (true) {
    int i = 0;
    int M , score = 0;
    int seed = 0;
    /*cout << "Please input a seed: \n";*/
    cin >> seed;
    if ( seed != -1 ){
        srand(seed);
        int N = rand() % 21;
        /*cout << N ;*/
        while (i < 10){
            i++;
            /*cout << "guess the random number zero to twenty: \n";*/
            cin >> M;
            if (M == N){
            score += 10;
            }
            else if (M<= N +1 && M >= N -1){
                score += 5;
            }
            else if (M <= N +3 && M >= N -3){
                score += 2;
            }
            else{
                score += 0;
            }   
        }
        float averagescore = score / 10.0;
        cout << /*"Your score is: " << */averagescore << " ";
    }
    else {
        /*cout << "game over";*/
        return 0;
    }
}
}
