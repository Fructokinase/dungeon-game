#include "human.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"

using namespace std;

class Cell;

Human::Human(Cell* spawnedIn, int row,int col):Enemy(spawnedIn, row, col), fieldIdentity('H'){
    Character::setStats(140, 20, 20);
}

Human::~Human(){}

void Human::beAttackedBy (Shade& s) {

    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Human::beAttackedBy (Vampire& v) {

    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();
    Character::hp-=damage;

    v.heal();

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Human::beAttackedBy (Goblin& g) {

    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
}

void Human::beAttackedBy (Troll& t) {

    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Human::beAttackedBy (Drow& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Human::attack(Player& p) {
    p.beAttackedBy(*this);
};

char Human::getFieldIdentity(){
    return fieldIdentity;
}

Info Human::getInfo() const {
    return Info{ Character::posX , Character::posY , true, ' ', ' ', nullptr, "human"};
}
