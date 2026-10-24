#include <iostream>
using namespace std;

class Monster{
    private:
        int speciesID;
        int hp;
        int level;
    public:
        Monster(int id = 0, int h = 0, int l = 1 );
        int power() const;
        int getHp() const;
        int getLevel() const;
        int getSpeciesId() const;
};

int Monster::power() const{
    int power = hp * level / 10;
    return power;
}

Monster::Monster(int id , int h , int l ){
    speciesID = id;
    hp = h;
    level = l;
}

int Monster::getHp() const{
    return hp;
}

int Monster::getLevel() const{
    return level;
}
 
int Monster::getSpeciesId() const{
    return speciesID;
}



class Team{ 
private:
    Monster* monsters;
    int capacity;
    int count;
public:
    Team();
    Team(const Team& t);
    ~Team();
    void add (const Monster& m);
    void release (int index);
    int getCount() const;
    int getTotalPower() const;
    Monster get(int i) const;
    Team& operator=(const Team& t);

    friend class Trainer;
};

Team::Team(const Team& t): capacity(t.capacity), count(t.count) {
    monsters = new Monster[capacity];
    for (int i = 0; i < count; i++) {
        monsters[i] = t.monsters[i];
    }
}

Team& Team::operator=(const Team& t){
    if (this == &t) return *this;
    Monster* newMonsters = new Monster[t.capacity];
    for (int i = 0 ; i < t.count; i++){
        newMonsters[i] = t.monsters[i];
    }
    delete[] monsters;
    monsters = newMonsters;
    capacity = t.capacity;
    count = t.count;
    return *this;
}

int Team::getTotalPower() const{
    int p = 0 ;
    for( int i = 0 ; i < count ; i++){
        p += monsters[i].power();
    }
    return p;
}

void Team::add(const Monster& m) {
    if (count >= capacity){
        capacity += 3 ;
        Monster* new_monsters =new Monster[capacity];
        for( int i = 0 ; i < count ; i++ ){
            new_monsters[i] = monsters[i];
        }
        delete[] monsters;
        monsters = new_monsters;
    }
    monsters[count] = m;
    count++ ;
}

int Team::getCount() const{
    return count;
}

Monster Team::get(int i) const{
    return monsters[i];
}

void Team::release (int index){
    if (index < 0 || index >= count) return;
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
    Trainer(const Trainer& t);
    void catchMonster (int id, int hp, int level);
    void releaseMonster(int index);
    double getAveragePower();
    Trainer& operator=(const Trainer& t);
    Trainer operator+ (const Trainer& t);
    Trainer& operator+= (const Trainer& t);
    Monster* operator[] (int i);
    Trainer& operator++ ();
    friend ostream& operator<< (ostream& os , const Trainer& t);
};

Trainer::Trainer(const Trainer& t): trainerID(t.trainerID), team(t.team) {}

Trainer& Trainer::operator++(){
    team.add(Monster(rand() ,rand(), rand()));
    return *this;
}

Monster* Trainer::operator[](int i){
    if(i > team.getCount() || i <= 0) return NULL;
    else return &team.monsters[i-1];
}

Trainer& Trainer::operator+= (const Trainer& t){
    trainerID += t.trainerID;
    for(int i = 0 ; i < t.team.getCount() ; i++){
        team.add(t.team.get(i));
    }
    return *this;
} 

Trainer Trainer::operator+(const Trainer& t){
    Trainer t0(0);
    t0.trainerID = trainerID + t.trainerID;
    for (int i = 0 ; i < team.getCount(); i++){
        t0.team.add(team.monsters[i]);
    }
    for(int i = 0 ; i <t.team.getCount() ;i++){
        t0.team.add(t.team.monsters[i]);
    }
    return t0;
}

Trainer::Trainer(int id):trainerID(id){}

ostream& operator<< (ostream& os , const Trainer& t){
    os << t.trainerID << " : " << t.team. getCount() ;
    return os;
}


Trainer& Trainer::operator=(const Trainer& t){
    trainerID = t.trainerID;
    team = t.team;
    return *this;
}

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



int main() {
    srand(100);
    Trainer t1(1);
    t1.catchMonster(25, 80, 5);
    t1.catchMonster(4, 120, 7);
    Trainer t2(2);
    t2.catchMonster(7, 100, 6);
    Trainer t3(3);
    t3.catchMonster(1, 110, 6);
    Trainer t4 = t2 + t3;
    t1 += t4;
    t1.releaseMonster(1);
    cout << t1.getAveragePower() << endl;
    t4 = t1;
    for (int i=0; i<3; i++, ++t4);
    cout << t4 << endl;
    Monster* m = t4[5];
    if (m != NULL) {
    cout << m->getSpeciesId() << "," << m->getHp()<< "," << m->getLevel() << endl;
    }
    else {
    cout << "out of range" << endl;
    }
    return 0;
}