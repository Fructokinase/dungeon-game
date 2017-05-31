#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;

class Merchant : public Enemy {

    // indicates if merchant should attack from now on
    static bool should_attack;

    char fieldIdentity;

public:
    Merchant(Cell*, int, int);
    ~Merchant();

    void attack (Player&) override;

    void beAttackedBy (Shade&) override;
    void beAttackedBy (Vampire&) override;
    void beAttackedBy (Goblin&) override;
    void beAttackedBy (Troll&) override;
    void beAttackedBy (Drow&) override;

    char getFieldIdentity() override;

    Info getInfo() const override;
};

#endif
