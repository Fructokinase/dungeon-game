#include "vampire.h"
#include "enemy.h"
#include <cmath>
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include "dragon.h"
#include <iostream>

using namespace std;

Vampire::Vampire(Cell* spawnedIn, int x, int y):Player(spawnedIn, x, y), perHeal(5){
    Player::init(50, 25, 25);
    Character::setHPBoundary(0, 2147483647);
};

Vampire::~Vampire(){};

void Vampire::attack(Enemy& e) {
    e.beAttackedBy(*this);
};

void Vampire::heal(){
    Character::hp+=perHeal;
    notifyObservers(SubscriptionType::textDisplay);
}

void Vampire::beAttackedBy (Human& h) {

    int damage = ceil(100.0 / (100 + Character::def)) * h.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

}

void Vampire::beAttackedBy (Dwarf& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

}

void Vampire::beAttackedBy(Halfling& l) {
    int damage = ceil(100.0 / (100 + Character::def)) * l.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

void Vampire::beAttackedBy(Elf& e) {
    int damage = ceil(100.0 / (100 + Character::def)) * e.getAtk();

    // elf gets two attacks against every race except drow
    for (int i = 0; i < 2; ++i) {
        if (rand() / 2 == 0) {
            damage = 0;
        }
        Character::hp-=damage;
        if(Character::hp < 0) Character::hp = 0;
        notifyObservers(SubscriptionType::textDisplay);
    }


    if(Character::hp <= 0) {
        Player::die();
    }

};

void Vampire::beAttackedBy (Orcs& o) {

    int damage = ceil(100.0 / (100 + Character::def)) * o.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

}

void Vampire::beAttackedBy(Merchant& m) {
    int damage = ceil(100.0 / (100 + Character::def)) * m.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

void Vampire::beAttackedBy(Dragon& d) {
    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }
};

int Vampire::getGold() {
    return Player::gold;
}

string Vampire::objectType() const {
    return "Vampire";
}


Info Vampire::getInfo() const {
    return Info{-1, -1, true, '@', ' ', nullptr, "Vampire", Character::hp, Character::atk, Character::def, Player::gold};
}
