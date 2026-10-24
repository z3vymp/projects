#include <iostream>
using namespace std;
#include <string>

class Monster{
    private:
        int speciesID;
        int hp;
        int level;
    public:
        Monster(int id = 0, int h = 0, int l = 1 );

        int power();
        int getHP();
        int getLevel();
        int getSpeciesID();
};

int Monster::power(){
    int power = hp * level / 10;
    return power;
}

Monster::Monster(int id, int h, int l){
    speciesID = id;
    hp = h;
    level = l;
}

int Monster::getHP(){
    return hp;
}

int Monster::getLevel(){
    return level;
}
 
int Monster::getSpeciesID(){
    return speciesID;
}



class Team{ 
private:
    Monster* monsters;
    int capacity;
    int count;
public:
    Team();
    ~Team();
    void add (const Monster& m);
    void release (int index);
    int getCount();
    int getTotalPower();
    Monster get(int i);
};

int Team::getTotalPower(){
    int p = 0 ;
    for( int i = 0 ; i < count ; i++){
        p += monsters[i].power();
    }
    return p;
}

void Team::add(const Monster& m) {
    if (count >= capacity){
        int new_capacity = capacity+3 ;
        Monster* new_monsters =new Monster[new_capacity];
        for( int i = 0 ; i < count ; i++ ){
            new_monsters[i] = monsters[i];
        }
        delete[] monsters;
        capacity = new_capacity;
        monsters = new_monsters;
    }
    monsters[count] = m;
    count++ ;
}

int Team::getCount(){
    return count;
}

Monster Team::get(int i){
    return monsters[i];
}

void Team::release (int index){
    monsters[index] = monsters[count-1];
    monsters[count-1] = 0 ;
    count-- ;
}

Team::~Team(){
    delete[] monsters;
}

Team::Team():capacity(3), count(0) {
    monsters = new Monster [capacity];
}



class Trainer {
private:
    int trainerID;
    Team team;
public:
    Trainer(int id);
    void catchMonster (int id, int hp, int level);
    void releaseMonster(int index);
    double getAveragePower();
};

Trainer::Trainer(int id):trainerID(id){}

void Trainer::catchMonster (int id, int hp, int level){
    Monster m ( id , hp , level );
    team.add(m);
}

void Trainer::releaseMonster(int index){
    team.release(index);
}

double Trainer::getAveragePower(){
    int p = team.getTotalPower();
    float c = team.getCount();
    double ave;
    if (c == 0) ave = 0.0;
    else ave = p/c;
    return ave;
}

int main(){
    Trainer t(1);
    t.catchMonster(25,80,5);
    t.catchMonster(4,120,7);
    t.catchMonster(7,100,6);
    t.catchMonster(1,110,6);
  
    t.releaseMonster(1);
    cout << t.getAveragePower() << endl;
      
    return 0;
}