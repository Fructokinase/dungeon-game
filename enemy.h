#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"
#include "subject.h"

class Cell;
class Shade;
class Admin;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;

class Enemy: public Character {
public:

    Enemy(Cell*, int, int);
    ~Enemy();

    // beAttackedBy methods
    virtual void beAttackedBy(Shade&)=0;
    virtual void beAttackedBy(Vampire&)=0;
    virtual void beAttackedBy(Goblin&)=0;
    virtual void beAttackedBy(Troll&)=0;
    virtual void beAttackedBy(Drow&)=0;
    void beAttackedBy(Admin&);

    // attack methods
    virtual void attack (Player&) =0;


    //void spawn() override;

    char getFieldIdentity() override;

    void move(int, int) override;

    string objectType() const override;

    void die() override;

};

#endif
