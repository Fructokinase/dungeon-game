#ifndef __SHADE_H_
#define __SHADE_H_

#include "player.h"
#include "cellinfo.h"

class Cell;

class Shade : public Player {
public:
    Shade(Cell*, int, int);
    ~Shade();

    void attack (Enemy&) override;

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
