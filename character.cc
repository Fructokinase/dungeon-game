#include "character.h"
#include "cell.h"
#include <iostream>

#include <cstdlib>

using namespace std;

Character::Character(Cell* spawnedIn, int x, int y):occupiedCell(spawnedIn), spawnedX(x), spawnedY(y), posX(x), posY(y) {};

Character::~Character() {};

char Character::getFieldIdentity(){
    return 'X';
}

void Character::setStats(int defaultHp, int defaultAtk, int defaultDef){
    hp = defaultHp;
    atk = defaultAtk;
    def = defaultDef;
}

void Character::setHPBoundary(int min, int max){
    minHP = min;
    maxHP = max;
}


// Getters

int Character::getHP() const {
    return hp;
}

int Character::getAtk() const {
    return atk;
}

int Character::getDef() const {
    return def;
}

void Character::changeCell(Cell* c){
    occupiedCell = c;
}

string Character::objectType() const {
    return "Character";
}
