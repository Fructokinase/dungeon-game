#include "dwarf.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
using namespace std;


Dwarf::Dwarf(Cell* spawnedIn, int row,int col): Enemy(spawnedIn, row, col), fieldIdentity('W') {
    Character::setStats(100, 20, 30);
}

Dwarf::~Dwarf() {};


void Dwarf::attack (Player &p) {
    p.beAttackedBy(*this);
    // Vampires are allergic to dwarves and lose 5HP rather than gain
    // this feature is implemented in vampire.cc
};

void Dwarf::beAttackedBy (Shade &s) {
    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Dwarf::beAttackedBy (Vampire &v) {

    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();

    Character::hp-=damage;

    v.heal();

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dwarf::beAttackedBy (Goblin &g) {

    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
}

void Dwarf::beAttackedBy (Troll &t) {

    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dwarf::beAttackedBy (Drow &d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

char Dwarf::getFieldIdentity(){
    return fieldIdentity;
};


Info Dwarf::getInfo() const {
    return Info {Character::posX , Character::posY , true, ' ', ' ', nullptr, "dwarf"};
};

