#ifndef __DWARF_H__
#define __DWARF_H__

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;

class Dwarf : public Enemy {

    char fieldIdentity;

public:
    Dwarf(Cell*, int, int);
    ~Dwarf();

    void attack (Player &p) override;

    void beAttackedBy (Shade&) override;
    void beAttackedBy (Vampire&) override;
    void beAttackedBy (Goblin&) override;
    void beAttackedBy (Troll&) override;
    void beAttackedBy (Drow&) override;

    char getFieldIdentity() override;

    Info getInfo() const override;
};

#endif
