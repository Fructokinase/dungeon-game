#ifndef __ENEMYFACTORY_H_
#define __ENEMYFACTORY_H_

#include "human.h"
#include "dwarf.h"
#include "halfling.h"
#include "elf.h"
#include "orcs.h"
#include "merchant.h"
#include <iostream>

using namespace std;

class Enemy;
class Cell;

Enemy* EnemyFactory(int enemyType, Cell* spawnedIn, int row, int col){

    if(enemyType < 4) {
        return new Human(spawnedIn, row, col);
    }

    else if ((enemyType >= 4) && (enemyType < 7)) {
        return new Dwarf(spawnedIn, row, col);
    }

    else if ((enemyType >= 7) && (enemyType < 12)) {
        return new Halfling(spawnedIn, row, col);
    }

    else if ((enemyType >= 12) && (enemyType < 14)) {
        return new Elf(spawnedIn, row, col);
    }

    else if ((enemyType >= 14) && (enemyType < 16)) {
        return new Orcs(spawnedIn, row, col);
    }

    else if ((enemyType >= 16) && (enemyType < 18)) {
        return new Merchant(spawnedIn, row, col);
    }
    else {
        return new Human(spawnedIn, row, col);
    }
}


#endif
