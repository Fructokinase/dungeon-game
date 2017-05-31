#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"
#include "cellinfo.h"

class Cell;
class Shade;
class Vampire;
class Goblin;
class Troll;
class Drow;
class Player;
class Gold;

class Dragon: public Enemy {

    char fieldIdentity;
    Gold *dh = nullptr;
    bool isGuarding;

public:

    Dragon(Gold*, Cell*, int, int);
    ~Dragon();

    bool isBusy();

    Gold *get_dh();
    void guardGold(Gold*);

    void move(int, int) override;

    void beAttackedBy(Shade&) override;
    void beAttackedBy(Vampire&) override;
    void beAttackedBy(Goblin&) override;
    void beAttackedBy(Troll&) override;
    void beAttackedBy(Drow&) override;

    void attack (Player&) override;

    char getFieldIdentity() override;

    Info getInfo() const override;
};


#endif
