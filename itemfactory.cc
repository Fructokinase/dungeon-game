#include "itemfactory.h"
#include <cstdlib>

Item* ItemFactory(itemType t){
    if(t == itemType::gold) {

        int whichGold = rand()%8;
        int value;

        if(whichGold < 6) {
            value = 2;
        } else if (whichGold == 7) {
            value = 6;
        } else {
            value = 1;
        }

        return new Gold(value);

    } else {

        int r = rand()%3;
        potionType randPotionType = static_cast<potionType>(r);
        int randPotionValue;
        int randSign = rand()%2;
        int sign = 1;
        if(randSign == 0) sign = -1;


        if(randPotionType == potionType::HP) {
            randPotionValue = sign * 10;
        } else {
            randPotionValue = sign * 5;
        }
        return new Potion(randPotionType, randPotionValue);
    }
}

// used for gold
Item* ItemFactory(itemType t, int value){
        return new Gold(value);
}

// use for potion
Item* ItemFactory(potionType p, int value){
    return new Potion{p, value};
}
