#ifndef __ELF_H__
#define __ELF_H__

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Troll;
class Drow;
class Player;

class Elf : public Enemy {

    char fieldIdentity;

public:
    Elf(Cell*, int, int);
    ~Elf();

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
