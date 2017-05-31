#ifndef __PLAYERFACTORY_H_
#define __PLAYERFACTORY_H_

#include "shade.h"
#include "admin.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"

class Player;
class Cell;

Player* PlayerFactory(int PlayerType, Cell* spawnedIn, int row, int col){

    if (PlayerType == 1){
        return new Drow(spawnedIn, row, col);
    } else if (PlayerType == 2){
        return new Troll(spawnedIn, row, col);
    } else if (PlayerType == 3){
        return new Vampire(spawnedIn, row, col);
    } else if (PlayerType == 4){
        return new Goblin(spawnedIn, row, col);
    } else if(PlayerType == 100){
        return new Admin(spawnedIn, row, col);
    } else {
        return new Shade(spawnedIn, row, col);
    }
}


#endif
