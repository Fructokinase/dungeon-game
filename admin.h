#ifndef __ADMIN_H_
#define __ADMIN_H_

#include "player.h"
#include "cellinfo.h"

class Cell;

class Admin : public Player {
public:
    Admin(Cell*, int, int);
    ~Admin();

    void attack (Enemy&) override;

    void beAttackedBy(Human&) override;
    void beAttackedBy(Dwarf&) override;
    void beAttackedBy(Halfling&) override;
    void beAttackedBy(Elf&) override;
    void beAttackedBy(Orcs&) override;
    void beAttackedBy(Merchant&) override;
    void beAttackedBy(Dragon&) override;


    string objectType() const override;

    Info getInfo() const override;
};


#endif
