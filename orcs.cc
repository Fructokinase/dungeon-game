#include "orcs.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
using namespace std;


Orcs::Orcs(Cell* spawnedIn, int row, int col): Enemy(spawnedIn, row, col), fieldIdentity('O') {
    Character::setStats(180, 30, 25);
}


Orcs::~Orcs() {}


void Orcs::attack (Player &p) {
    p.beAttackedBy(*this);
};


void Orcs::beAttackedBy (Shade &s) {
    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Orcs::beAttackedBy (Vampire &v) {
    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();

    Character::hp-=damage;

    v.heal();

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Orcs::beAttackedBy (Goblin &g) {
    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
};

void Orcs::beAttackedBy (Troll &t) {
    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Orcs::beAttackedBy (Drow &d) {
    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};


char Orcs::getFieldIdentity(){
    return fieldIdentity;
};


Info Orcs::getInfo() const {
    return Info {Character::posX , Character::posY , true, ' ', ' ', nullptr, "orcs"};
};

