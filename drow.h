#ifndef __DROW_H_
#define __DROW_H_

#include "player.h"
#include "cellinfo.h"

class Cell;
class Potion;

class Drow : public Player {
public:
    Drow(Cell*, int, int);
    ~Drow();

    void attack (Enemy&) override;

    void usePotion(Potion*) override;

    void beAttackedBy(Human&) override;
    void beAttackedBy(Dwarf&) override;
    void beAttackedBy(Halfling&) override;
    void beAttackedBy(Elf&) override;
    void beAttackedBy(Orcs&) override;
    void beAttackedBy(Merchant&) override;
    void beAttackedBy(Dragon&) override;

    int getGold() override;

    string objectType() const override;

    Info getInfo() const override;
};


#endif
