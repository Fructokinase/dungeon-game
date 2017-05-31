#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <string>
#include <vector>
#include "cellinfo.h"
#include "subject.h"
#include "observer.h"
#include "itemtype.h"
#include "potiontype.h"
#include "dragon.h"

using namespace std;

class FieldObject;
class Map;
class Enemy;
class Player;
class Admin;
class Item;
class Gold;

struct Info;

class Cell: public Subject, public Observer {

    char cellType;
    char chamber;
    bool isOccupied;
    FieldObject* whatIsOccupied;

    int row;
    int col;

    Map* map;

    const vector<char> validCellType = {'|', '-', '#', '+', '.', ' ', '\\', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '@', 'H', 'W', 'L', 'E', 'M', 'O', 'D'};
public:
    //ctor dtor
    //CellType is one of ('|' , '_', '#', '+', '.', ' ')
    Cell(char cellType, char, Map* m);
    ~Cell();

    FieldObject* spawnLayout();

    bool getIsOccupied();

    bool reachedStairs();

    //getters and setters
    void setCoords(int, int);
    Info getInfo() const override;

    //sets the chamber number
    void setChamber(int);

    //set cellType;
    void setCellType(char);
    char getCellType();

    //cell actions
    void occupy(FieldObject*);
    void unOccupy();


    // spwawns the player in this cell, or places a player in this cell
    Player* spawnPlayer(string);
    void spawnPlayer(Player*);

    // spawns an enemy in this cell
    Enemy* spawnEnemy();
    Enemy* spawnEnemy(int);

    // spwans a dragon in this cell
    Enemy* spawnDragon(Gold*);

    // spawn an item, gold or potion, in this cell
    Item* spawnItem(itemType);
    Item* spawnItem(itemType, int);
    Item* spawnItem(potionType, int);

    // move restrictions
    bool canMoveTo(Enemy*, int, int);
    bool canMoveTo(Player*, int, int);

    // gets the pointer to Cell at row+dx, col+dy
    // Requires : canMoveTo(dx, dy) == true
    Cell* getPtrTo(int , int );

    void update(Subject &whoNotified) override;

    SubscriptionType subType() const override;

};

#endif
