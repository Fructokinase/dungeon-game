#ifndef __CELLINFO_H__
#define __CELLINFO_H__

#include <string>

class FieldObject;

using namespace std;

struct Info {
    int row, col;
    bool isOccupied;
    char cellType;
    char chamber;
    FieldObject* whatIsOccupied;
    string race;
    int hp, atk, def, gold;
};

#endif
