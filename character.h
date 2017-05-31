#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "fieldobject.h"
#include "subject.h"
#include <string>

using namespace std;

class Cell;

class Character: public FieldObject, public Subject {
protected:
    Cell* occupiedCell;

    const int spawnedX;
    const int spawnedY;

    int posX;
    int posY;

    int hp;
    int atk;
    int def;

    int minHP;
    int maxHP;

    // sets hp, atk, and def
    void setStats(int, int, int);

    // set min and max hp
    void setHPBoundary(int, int);


public:

    Character(Cell*, int, int);
    ~Character();

    virtual void move(int, int)=0;

    //void spawn() override;

    char getFieldIdentity() override;

    //void die() override;

    int getHP() const ;
    int getAtk() const ;
    int getDef() const ;

    string objectType() const override;

    void changeCell(Cell*);

    virtual void die()=0;


};

#endif
