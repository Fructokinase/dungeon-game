#include "elf.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
using namespace std;

Elf::Elf(Cell* spawnedIn, int row, int col): Enemy(spawnedIn, row, col), fieldIdentity('E') {
    Character::setStats(140, 30, 10);
}

Elf::~Elf() {}


void Elf::attack (Player &p) {
    p.beAttackedBy(*this);
};

void Elf::beAttackedBy (Shade &s) {
    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Elf::beAttackedBy (Vampire &v) {
    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();

    Character::hp-=damage;

    v.heal();

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Elf::beAttackedBy (Goblin &g) {
    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
};

void Elf::beAttackedBy (Troll &t) {
    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Elf::beAttackedBy (Drow &d) {
    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

char Elf::getFieldIdentity() {
    return fieldIdentity;
};

Info Elf::getInfo() const {
    return Info {Character::posX , Character::posY , true, ' ', ' ', nullptr, "elf"};
};

