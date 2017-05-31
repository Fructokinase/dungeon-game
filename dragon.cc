#include "dragon.h"
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

Dragon::Dragon(Gold* dh, Cell* spawnedIn, int row,int col):Enemy(spawnedIn, row, col), fieldIdentity('D'), dh{dh}, isGuarding{false} {
    Character::setStats(150, 20, 20);
}

Dragon::~Dragon(){
    dh = nullptr;
}

bool Dragon::isBusy(){
    return isGuarding;
}


Gold *Dragon::get_dh() {
    return dh;
}

void Dragon::guardGold(Gold* g) {
    dh = g;
    isGuarding = true;
}

void Dragon::move(int, int){
    return;
}


void Dragon::beAttackedBy (Shade& s) {

    int damage = ceil(100.0 / (100 + Character::def)) * s.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dragon::beAttackedBy (Vampire& v) {

    int damage = ceil(100.0 / (100 + Character::def)) * v.getAtk();
    Character::hp-=damage;

    v.heal();

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dragon::beAttackedBy (Goblin& g) {

    int damage = ceil(100.0 / (100 + Character::def)) * g.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        g.rob();
        Enemy::die();
    }
}

void Dragon::beAttackedBy (Troll& t) {

    int damage = ceil(100.0 / (100 + Character::def)) * t.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dragon::beAttackedBy (Drow& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();
    Character::hp-=damage;

    if(Character::hp <= 0) {
        Enemy::die();
    }
}

void Dragon::attack(Player& p) {
    p.beAttackedBy(*this);
};

char Dragon::getFieldIdentity(){
    return fieldIdentity;
}

Info Dragon::getInfo() const {
    return Info{ Character::posX , Character::posY , true, ' ', ' ', nullptr, "dragon"};
}

