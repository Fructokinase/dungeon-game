#ifndef __GOBLIN_H_
#define __GOBLIN_H_

#include "player.h"
#include "cellinfo.h"

class Cell;

class Goblin : public Player {
    int perRob;
public:
    Goblin(Cell*, int, int);
    ~Goblin();

    void attack (Enemy&) override;

    void beAttackedBy(Human&) override;
    void beAttackedBy(Dwarf&) override;
    void beAttackedBy(Halfling&) override;
    void beAttackedBy(Elf&) override;
    void beAttackedBy(Orcs&) override;
    void beAttackedBy(Merchant&) override;
    void beAttackedBy(Dragon&) override;

    int getGold() override;
    void rob();

    string objectType() const override;

    Info getInfo() const override;
};


#endif
