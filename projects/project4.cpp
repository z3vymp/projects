#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

class Round{
    int* s;
    size_t count ;
    size_t size ;

public:
    Round();
    ~Round();
    void Play(int N);
    Round* Merge2(Round* r2);
    float ReportAve();
};

void Round::Play(int N){
    int M = 0;
    int sco = 0;
    while (true){
        cout << "input a number" << endl;
        cin >> M;
        if ( M < 0 || M >20 ) break;
        if ( M == N) {
            sco = 10;
        }
        else if ( M <= N+1 && M >= N-1){
            sco = 5;
        }
        else if (M <= N +3 && M >= N -3){
            sco = 2;
        }
        else{
            sco = 0;
        }
        if (size <= count){
            int new_size = size*2;
            int* new_s = new int [new_size];
            for(int i = 0; i < count; i++){
                new_s[i] = s [i];
            }
            size = new_size;
            delete [] s;
            s = new_s;
        }
        s[count] = sco;
        count++;
    }
}
//s中写入每次猜测的分数

float Round::ReportAve () {
    int sum = 0;
    float ave;
    for ( int i = 0; i < count ; i++){
        sum += s[i];
        ave = sum/(float)count;
    }
return ave;
}
//返回每轮游戏平均分

Round* Round::Merge2(Round* r2){
    Round* r = new Round;
    r->count = count + r2->count;
    r->size = r->count;
    delete[] r ->s;
    r->s = new int[r->size];
    for(int i = 0; i < count ; i++){
        r->s[i] = s[i];
    }
    for(int i = 0; i < r2->count ; i++){
        r->s[count+i] = r2->s[i];
    }
    return r;
}
//融合

Round::Round (): count(0) ,size(2) {
    s = new int [size];
}
//构造

Round::~Round () {
    delete[] s;
}
//析构


class Game {
    Round** r;
    size_t count;
    size_t size;
public:
    Game();
    ~Game();
    void Play();
    float Calculate();
};

Game::Game():count(0),size(2){
    r = new Round*[size];
}
Game::~Game(){
    for(int i = 0; i < count ; i++){
        delete r[i];
    }
    delete [] r;
}

void Game::Play(){
    int seed;
    while (true){
        cout << "input the seed " << endl;
        cin >> seed;

        if (seed == -1) break;
        srand(seed);
        int N = rand() % 21;

        if (size <= count){
            int new_size = size*2;
            Round** new_r = new Round* [new_size];
            for(int i = 0; i < count; i++){
                new_r[i] = r [i];
            }
            size = new_size;
            delete [] r;
            r = new_r;
        }
        r[count] = new Round;   
        r[count]->Play(N);
        count++;
    }   
}

float Game::Calculate(){
    Round* r1 = r[0];
    Round* r2 = r[count-1];
    Round* rx = r1->Merge2(r2);
    float ave = rx->ReportAve();
    return ave;
}
//计算融合平均分

int main() {
    Game g;
    g.Play();
    cout << g.Calculate() <<endl;
    return 0;
}
