#include "halfling.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
using namespace std;

Halfling::Halfling(Cell* spawnedIn, int row, int col): Enemy(spawnedIn, row, col), fieldIdentity('L') {
    Character::setStats(100, 15, 20);
}

Halfling::~Halfling() {}


void Halfling::attack (Player &p) {
    p.beAttackedBy(*this);
};

void Halfling::beAttackedBy (Shade &s) {
    // Halflings have a 50% chance to cause the player character to miss in combat
    // i.e. takes priority over player character’s ability to never miss

    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();

    if (rand() % 2 == 0) {
        damage = 0;
    }

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Halfling::beAttackedBy (Vampire &v) {
    // Halflings have a 50% chance to cause the player character to miss in combat
    // i.e. takes priority over player character’s ability to never miss

    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();

    if (rand() % 2 == 0) {
        damage = 0;
        return;
    }

    v.heal();

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Halfling::beAttackedBy (Goblin &g) {
    // Halflings have a 50% chance to cause the player character to miss in combat
    // i.e. takes priority over player character’s ability to never miss

    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();

    if (rand() % 2 == 0) {
        damage = 0;
        return;
    }

    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
}

void Halfling::beAttackedBy (Troll &t) {
    // Halflings have a 50% chance to cause the player character to miss in combat
    // i.e. takes priority over player character’s ability to never miss

    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();

    if (rand() % 2 == 0) {
        damage = 0;
        return;
    }

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Halfling::beAttackedBy (Drow &d) {
    // Halflings have a 50% chance to cause the player character to miss in combat
    // i.e. takes priority over player character’s ability to never miss

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    if (rand() % 2 == 0) {
        damage = 0;
        return;
    }

    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}


char Halfling::getFieldIdentity() {
    return fieldIdentity;
};

Info Halfling::getInfo() const {
    return Info {Character::posX , Character::posY , true, ' ', ' ', nullptr, "halfling"};
};

