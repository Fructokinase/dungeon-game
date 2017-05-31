#ifndef __ORCS_H__
#define __ORCS_H__

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;

class Orcs : public Enemy {

    char fieldIdentity;

public:
    Orcs(Cell*, int, int);
    ~Orcs();

    void attack (Player &p) override;

    // does 50% more damage to goblins
    void beAttackedBy (Shade &s) override;
    void beAttackedBy (Vampire &v) override;
    void beAttackedBy (Goblin&) override;
    void beAttackedBy (Troll&) override;
    void beAttackedBy (Drow&) override;


    char getFieldIdentity() override;

    Info getInfo() const override;
};


#endif
