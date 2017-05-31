#include "gold.h"

Gold::Gold(int val):t(itemType::gold), value(val), can_be_picked{true}, guard{nullptr} {
    if (val == 6) {
        can_be_picked = false;
    }
};

Gold::~Gold(){
    guard = nullptr;
};

bool Gold::get_bool() {
    return can_be_picked;
}

void Gold::modi_bool() {
    can_be_picked = true;
}

void Gold::set_guard(Dragon *g) {

    if(value != 6) return ;

    guard = g;
}

Dragon *Gold::get_guard() {

    return guard;
}

int Gold::getValue() {
    return value;
}

char Gold::getFieldIdentity(){
    return 'G';
}

string Gold::objectType() const {
    return "Gold";
}
