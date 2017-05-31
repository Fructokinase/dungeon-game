#include "merchant.h"
#include <iostream>
#include <cmath>
#include "itemfactory.h"
#include "shade.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
using namespace std;

bool Merchant::should_attack = false;

Merchant::Merchant(Cell* spawnedIn, int row, int col): Enemy(spawnedIn, row, col), fieldIdentity('M') {
    Character::setStats(30, 70, 5);
}

Merchant::~Merchant() {}

void Merchant::attack (Player &p) {
    if (should_attack) {
        p.beAttackedBy(*this);
    }
};

void Merchant::beAttackedBy (Shade &s) {
    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();

    Character::hp-=damage;

    // one merchant has been attacked, so from now on, all the merchants will attack you
    should_attack = true;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Merchant::beAttackedBy (Vampire &v) {
    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();

    Character::hp-=damage;

    // one merchant has been attacked, so from now on, all the merchants will attack you
    should_attack = true;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Merchant::beAttackedBy (Goblin &g) {
    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();

    Character::hp-=damage;

    // one merchant has been attacked, so from now on, all the merchants will attack you
    should_attack = true;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Merchant::beAttackedBy (Drow &d) {
    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    Character::hp-=damage;

    // one merchant has been attacked, so from now on, all the merchants will attack you
    should_attack = true;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

void Merchant::beAttackedBy (Troll &t) {
    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();

    Character::hp-=damage;

    // one merchant has been attacked, so from now on, all the merchants will attack you
    should_attack = true;

    if(Character::hp <= 0) {
        Enemy::die();
    }
};

char Merchant::getFieldIdentity(){
    return fieldIdentity;
};


Info Merchant::getInfo() const {
    return Info {Character::posX , Character::posY , true, ' ', ' ', nullptr, "merchant"};
};


