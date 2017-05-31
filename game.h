#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <string>
#include <vector>
#include "observer.h"

using namespace std;

class Map;
class Player;

class Game: public Observer{

    vector<Map> m;
    int currentFloor;

    const int NUM_FLOOR;
    const int BEGINNING_FLOOR;
    const int WINNING_FLOOR;

    vector<string> mapLayout;
    vector<string> chamberLayout;

    Player* p;

    bool positionDetermined;

public:
    //ctor dtor
    Game(string, string, int);
    ~Game();

    //init method;
    //
    void init(string race);
    void init(string race, bool);

    //moves the player in the direction specified
    int movePlayer(int, int);
    int movePlayer(string);

    // attacks in the diretion specified
    void attack(string);

    //gets called every turn
    int nextTurn();

    // when a player attempts to use potion;
    void usePotion(string);

    void update(Subject &whoNotified) override;

    int changeFloor(int);

    void freezeEnemies();

    int getScore();

    string getRawString();

    SubscriptionType subType() const override;

    friend ostream &operator<<(ostream &out, const Game &g);
};

#endif
