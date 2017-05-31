#include "potion.h"

Potion::Potion(potionType p, int val):t(itemType::potion), p(p), value(val){};
Potion::~Potion(){};

potionType Potion::getType() {
    return p;
}

int Potion::getValue() {
    return value;
}

void Potion::setValue(int v) {
    value = v;
}

char Potion::getFieldIdentity(){
    return 'P';
}

string Potion::getName(){

    if(p == potionType::HP){

        if(value > 0) {
            return "RH";
        }

        return "PH";
    }

    if(p == potionType::Atk){

        if(value > 0) {
            return "BA";
        }

        return "WA";
    }

    if(value > 0){
        return "BD";
    } else {
        return "WD";
    }
}

string Potion::objectType() const {
    return "Potion";
}
