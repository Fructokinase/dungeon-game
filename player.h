#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "character.h"
#include <string>
#include <iostream>

using namespace std;

class Cell;
class Gold;
class Potion;
class Enemy;
class Human;
class Dwarf;
class Halfling;
class Elf;
class Orcs;
class Merchant;
class Dragon;

class Player : public Character {
protected:
    int gold;
    char fieldIdentity;
    int floorAtkBoost;
    int floorDefBoost;

public:
    Player(Cell*, int, int);
    ~Player();

    void init(int, int, int);

    void changeGold(Gold*);
    void changeGold(int);

    virtual int getGold();

    int getRow();
    int getCol();

    void setRow(int);
    void setCol(int);

    virtual void move(int, int) override;
    virtual void attack (Enemy&) =0;

    // be attack by methods
    virtual void beAttackedBy(Human&)=0;
    virtual void beAttackedBy(Dwarf&)=0;
    virtual void beAttackedBy(Halfling&)=0;
    virtual void beAttackedBy(Elf&)=0;
    virtual void beAttackedBy(Orcs&)=0;
    virtual void beAttackedBy(Merchant&)=0;
    virtual void beAttackedBy(Dragon&)=0;

    virtual void usePotion(Potion*);

    char getFieldIdentity() override;

    string objectType() const override;

    void leaveMap();

    void die() override;

    friend std::ostream &operator<<(std::ostream &out, const Player&);

};


#endif
