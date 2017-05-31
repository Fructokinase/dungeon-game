#ifndef __HUMAN_H_
#define __HUMAN_H_

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;

class Human: public Enemy {

    char fieldIdentity;

public:

    Human(Cell*, int, int);
    ~Human();

    void beAttackedBy(Shade&) override;
    void beAttackedBy(Vampire&) override;
    void beAttackedBy(Goblin&) override;
    void beAttackedBy(Troll&) override;
    void beAttackedBy(Drow&) override;

    void attack (Player&) override;

    char getFieldIdentity() override;

    Info getInfo() const override;
};


#endif
