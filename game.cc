#include "game.h"
#include "map.h"
#include "itemtype.h"
#include "mapstate.h"

using namespace std;


//helper function that splits the map up into pieces
std::vector<std::string> Split(const std::string& str, int splitLength)
{
   int NumSubstrings = str.length() / splitLength;
   std::vector<std::string> ret;

   for (auto i = 0; i < NumSubstrings; i++)
   {
        ret.push_back(str.substr(i * splitLength, splitLength));
   }

   // If there are leftover characters, create a shorter item at the end.
   if (str.length() % splitLength != 0)
   {
        ret.push_back(str.substr(splitLength * NumSubstrings));
   }


   return ret;
}

Game::Game(string inputLayout, string cl, int f):NUM_FLOOR(f), BEGINNING_FLOOR(1), WINNING_FLOOR(NUM_FLOOR),p(nullptr){
    mapLayout = Split(inputLayout, 1975);

    if(cl.length() > 0){
        chamberLayout = Split(cl, 1975);
        positionDetermined = false;
    } else {
        chamberLayout.emplace_back("");
        positionDetermined = true;
    }

    currentFloor = BEGINNING_FLOOR;
    m.reserve(NUM_FLOOR);
    m.emplace_back(Map{});
};

Game::~Game(){
    delete p;
};

void Game::init(string playerRace) {
    m.back().init(mapLayout[0], chamberLayout[0], currentFloor);
    p = m.back().spawnPlayer(playerRace);
    p->attach(this);
    m.back().spawnStair();
    m.back().spawnItems(itemType::potion, 10);
    m.back().spawnItems(itemType::gold, 10);
    m.back().spawnEnemies(20);
}

void Game::init(string playerRace, bool positionGiven) {
    m.back().init(mapLayout[0], currentFloor);
    p = m.back().spawnPlayer(playerRace);
    p->attach(this);
    m.back().spawnEnemies();
}


int Game::changeFloor(int change){

    p = m.back().getPlayerPtr();

    p->dettach(&m.back());
    p->leaveMap();

    if(currentFloor == WINNING_FLOOR) return p->getGold();

    currentFloor++;

    m.emplace_back(Map{});

    if(!positionDetermined){
        m.back().init(mapLayout[currentFloor - 1] , chamberLayout[currentFloor - 1], currentFloor);
        m.back().spawnPlayer(p);
        m.back().spawnStair();
        m.back().spawnItems(itemType::potion, 10);
        m.back().spawnItems(itemType::gold, 10);
        m.back().spawnEnemies(20);
    } else {
        m.back().init(mapLayout[currentFloor - 1], currentFloor);
        m.back().spawnPlayer(p);
        m.back().spawnEnemies();
    }

    return -1;
}

int Game::movePlayer(int dx, int dy){

    mapState s = m.back().movePlayer(dx, dy);

    if(s == mapState::win && currentFloor == WINNING_FLOOR) return 2;

    return 1;
}

int Game::movePlayer(string direction){

    mapState s = m.back().movePlayer(direction);

    if(s == mapState::win && currentFloor == WINNING_FLOOR) return 2;

    return 1;
}

void Game::attack(string direction){
    int dx;
    int dy;

    if(direction == "no") {
        dx = -1;
        dy = 0;
    } else if (direction == "so") {
        dx = 1;
        dy = 0;
    } else if(direction == "ea") {
        dx = 0;
        dy = 1;
    } else if (direction == "we") {
        dx = 0;
        dy = -1;
    } else if (direction == "ne") {
        dx = -1;
        dy = 1;
    } else if (direction == "nw") {
        dx = -1;
        dy = -1;
    } else if (direction == "se") {
        dx = 1;
        dy = 1;
    } else if (direction == "sw") {
        dx = 1;
        dy = -1;
    } else {
        dx = 0;
        dy = 0;
    }

    m.back().attack(dx, dy);
}

// turns the game to the next frame and return the status of the game
int Game::nextTurn(){

    mapState s = m.back().nextTurn();

    if(s == mapState::normal) return 1;

    if(s == mapState::playerDead) return 0;

    if(s == mapState::win) return 2;

    return -1;

}

void Game::usePotion(string direction){

    int dx;
    int dy;

    if(direction == "no") {
        dx = -1;
        dy = 0;
    } else if (direction == "so") {
        dx = 1;
        dy = 0;
    } else if(direction == "ea") {
        dx = 0;
        dy = 1;
    } else if (direction == "we") {
        dx = 0;
        dy = -1;
    } else if (direction == "ne") {
        dx = -1;
        dy = 1;
    } else if (direction == "nw") {
        dx = -1;
        dy = -1;
    } else if (direction == "se") {
        dx = 1;
        dy = 1;
    } else if (direction == "sw") {
        dx = 1;
        dy = -1;
    } else {
        dx = 0;
        dy = 0;
    }

    m.back().usePotion(dx, dy);
}

void Game::freezeEnemies(){
    m.back().freezeEnemies();
}

int Game::getScore(){
    if(p == nullptr) return 0;

    return p->getGold();
}

// used when the player changes floor
void Game::update(Subject &whoNotified) {
    Game::changeFloor(1);
}

string Game::getRawString(){
    return m.back().getRawString();
}

SubscriptionType Game::subType() const {
  return SubscriptionType::game;
}

ostream &operator<<(ostream &out, const Game &g){

    if(g.m.empty()) {
        out << "map failed to load" << endl;
        return out;
    }

    out << g.m.back();
    return out;
}
