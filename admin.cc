#include "admin.h"
#include "enemy.h"
#include <cmath>
#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include <iostream>

using namespace std;

Admin::Admin(Cell* spawnedIn, int x, int y): Player(spawnedIn, x, y){
    Player::init(99999999, 99999999, 99999999);
};

Admin::~Admin(){};

void Admin::attack(Enemy& e) {
    e.beAttackedBy(*this);
};

void Admin::beAttackedBy (Human& h) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
}

void Admin::beAttackedBy (Dwarf& d) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
}

void Admin::beAttackedBy(Halfling& l) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
};

void Admin::beAttackedBy(Elf& e) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
};

void Admin::beAttackedBy(Orcs& o) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
};

void Admin::beAttackedBy(Merchant& m) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
};

void Admin::beAttackedBy(Dragon& d) {
    Player::gold+=999;
    notifyObservers(SubscriptionType::textDisplay);
};

string Admin::objectType() const {
    return "Admin";
}

Info Admin::getInfo() const {
    return Info{-1, -1, true, '@', ' ',nullptr, "Admin", Character::hp, Character::atk, Character::def, Player::gold};
}
