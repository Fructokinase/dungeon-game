#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "enemy.h"
#include "player.h"
#include "itemtype.h"
#include "mapstate.h"

using namespace std;

class TextDisplay;
class Gold;

class Map : public Observer {

    const int COL_NUM;
    const int ROW_NUM;

    vector<vector<Cell>> grid;

    Player* p;
    // used to place a player on the board
    int playerSpawnR = -1;
    int playerSpawnC = -1;

    vector<Enemy*> enemies;
    int enemy_num;

    TextDisplay* td;

    int stairChamber = '0';

    mapState s;

    char playerChamber = '0';

    bool enemiesFrozen;

    friend Cell;

    void assignDragonHoardProtection();
    void lookforDragon(Gold* , int, int);

public:
    //ctor dtor
    Map();
    ~Map();

    //init method;
    // when the default map is used
    void init(string&, string&, int);
    // when all the position of player, stair, items, and enemies are given
    void init(string&, int);

    // generates character
    Player* spawnPlayer(string);
    void spawnPlayer(Player*p);

    //generates staircase
    void spawnStair();

    //speciefic spanwns
    // spawns a given number of enemies randomly
    void spawnEnemies(int);
    // when the positions are given
    void spawnEnemies();

    // spawn items, gold or potion
    void spawnItems(itemType, int);

    // spawn dragon given dragon hoard's coords
    void spawnDragon(Gold*, int , int);

    // moves the player;
    mapState movePlayer(int, int);
    mapState movePlayer(string);

    void attack(int, int);

    //turn method;
    mapState nextTurn();

    void freezeEnemies();

    SubscriptionType subType() const override;

    void update(Subject&) override;

    // use potion
    void usePotion(int, int);

    Player* getPlayerPtr();

    string getRawString();

    friend ostream &operator<<(ostream &out, const Map &m);
};

#endif
