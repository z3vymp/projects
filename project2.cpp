#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int compScore ( int N ,int M ){
    int score = 0;
    if (M == N)
	{
        score += 10;
    }
    else if (M<= N +1 && M >= N -1)
    {
        score += 5;
    }
	else if (M <= N +3 && M >= N -3)	
    {
        score += 2;
    }
    else
    {
        score += 0;
    }
    return score;
}//单次游戏算分函数


int main() {
    int j = 0;
    float sum = 0;
    float ave =0;
    float s1 = 0;
    float s = 0;
    float scores[10] {0};
    for (j = 0; j < 10; j++){
        int i = 0;
        int M , score = 0;
        int seed = 0;
        cout << "Please input a seed (input -1 to quit): \n";
        cin >> seed;
        if ( seed != -1 ){
            srand(seed);
            int N = rand() % 21;
            /*cout << N ;*/
            while (i < 10){
                i++;
                cout << "guess the random number zero to twenty: \n";
                cin >> M;
                    while ( M < 0 || M > 20){
                        cerr << "illegal ,input again\n";
                        cin >> M;  
                    }
                score += compScore(N, M);//调用算分函数
            }
        float averagescore = score / 10.0;
        cout << "Your score is: " << averagescore << " " << endl;
        scores[j] = averagescore;
        }
        else {
            cout << "game over" << endl;
            break;
        }
    }
    /*cout << j ; */
    for ( int m = 0 ; m < j ; m++){
        sum += scores[m] ;
        ave = sum/(float)j;
    }
    for ( int m = 0 ; m < j ; m++){
        s1 += pow(scores[m]-ave,2) ;
    }
    s = sqrt(s1/j);
    cout << "得分标准差为" << s << endl;
    return 0;
}


