#ifndef __TROLL_H_
#define __TROLL_H_

#include "player.h"
#include "cellinfo.h"

class Cell;

class Troll : public Player {
    int perHeal;
public:
    Troll(Cell*, int, int);
    ~Troll();

    void attack (Enemy&) override;

    void heal();

    void move(int, int) override;

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
