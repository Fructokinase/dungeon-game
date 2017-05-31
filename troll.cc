#include "troll.h"
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

Troll::Troll(Cell* spawnedIn, int x, int y): Player(spawnedIn, x, y),perHeal(5){
    Player::init(120, 25, 15);
    Character::setHPBoundary(0, 120);
};

Troll::~Troll(){};

void Troll::move(int dx, int dy) {
    Player::move(dx, dy);
    Troll::heal();
}

void Troll::attack(Enemy& e) {
    e.beAttackedBy(*this);
    Troll::heal();
};

void Troll::heal(){
    Character::hp+=perHeal;
    if(Character::hp > Character::maxHP) Character::hp = Character::maxHP;
    notifyObservers(SubscriptionType::textDisplay);
}

void Troll::beAttackedBy (Human& h) {

    int damage = ceil(100.0 / (100 + Character::def)) * h.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

}

void Troll::beAttackedBy (Dwarf& d) {

    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }
}

void Troll::beAttackedBy(Halfling& l) {
    int damage = ceil(100.0 / (100 + Character::def)) * l.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

void Troll::beAttackedBy(Elf& e) {
    int damage = ceil(100.0 / (100 + Character::def)) * e.getAtk();

    // elf gets two attacks against every race except drow
    for (int i = 0; i < 2; ++i) {
        if (rand() % 2 == 0) {
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

void Troll::beAttackedBy(Orcs& o) {
    int damage = ceil(100.0 / (100 + Character::def)) * o.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

void Troll::beAttackedBy(Merchant& m) {
    int damage = ceil(100.0 / (100 + Character::def)) * m.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

void Troll::beAttackedBy(Dragon& d) {
    int damage = ceil(100.0 / (100 + Character::def)) * d.getAtk();

    if (rand() % 2 == 0) damage = 0;

    Character::hp-=damage;
    if(Character::hp < 0) Character::hp = 0;
    notifyObservers(SubscriptionType::textDisplay);

    if(Character::hp <= 0) {
        Player::die();
    }

};

int Troll::getGold() {
    return Player::gold;
}

string Troll::objectType() const {
    return "Troll";
}


Info Troll::getInfo() const {
    return Info{-1, -1, true, '@', ' ', nullptr, "Troll", Character::hp, Character::atk, Character::def, Player::gold};
}
