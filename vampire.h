#ifndef __VAMPIRE_H_
#define __VAMPIRE_H_

#include "player.h"
#include "cellinfo.h"

class Cell;

class Vampire : public Player {
    int perHeal;
public:
    Vampire(Cell*, int, int);
    ~Vampire();

    void attack (Enemy&) override;

    void beAttackedBy(Human&) override;
    void beAttackedBy(Dwarf&) override;
    void beAttackedBy(Halfling&) override;
    void beAttackedBy(Elf&) override;
    void beAttackedBy(Orcs&) override;
    void beAttackedBy(Merchant&) override;
    void beAttackedBy(Dragon&) override;

    void heal();

    int getGold() override;

    string objectType() const override;

    Info getInfo() const override;
};


#endif
