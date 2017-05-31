#include "map.h"
#include "textdisplay.h"
#include <cstdlib>
#include "cellinfo.h"
#include "potion.h"
#include <algorithm>
#include <iterator>
#include "itemtype.h"
#include "actiontype.h"
#include "actioninfo.h"
#include "gold.h"
#include "dragon.h"

Map::Map():COL_NUM(79), ROW_NUM(25), p(nullptr), enemy_num(0), td(nullptr), s(mapState::normal), enemiesFrozen(false){};

Map::~Map(){
    delete td;
};


// init
void Map::init(string& map_layout, string& cl, int f){

    //initializes the text display;
    td = new TextDisplay(ROW_NUM, COL_NUM, f, map_layout);

    string::iterator it=map_layout.begin();
    char cell_layout;

    string::iterator cit=cl.begin();
    char chamber_layout;

    //initializes a 2-D vector of Cells
    for(int i = 0; i < ROW_NUM; i++) {

        vector<Cell> tmp;

        for (int j = 0; j < COL_NUM; j++){

            cell_layout = *it;
            chamber_layout = *cit;

            //constructs a cell with the cell_layout
            // for example if cell_layout is '-' or '|' it means that this cell is part of the wall
            tmp.push_back(Cell{cell_layout, chamber_layout, this});
            tmp.back().setCoords(i, j);
            tmp.back().attach(td);

            ++it;
            ++cit;
        }

        grid.push_back(tmp);
    }

}

// init when the positions are given
void Map::init(string& map_layout, int f){

    //initializes the text display;
    td = new TextDisplay(ROW_NUM, COL_NUM, f, map_layout);

    string::iterator it=map_layout.begin();
    char cell_layout;

    //initializes a 2-D vector of Cells
    for(int i = 0; i < ROW_NUM; i++) {

        vector<Cell> tmp;

        for (int j = 0; j < COL_NUM; j++){

            cell_layout = *it;

            // used to set initial player location
            if(cell_layout == '@'){
                playerSpawnR = i;
                playerSpawnC = j;
                cell_layout = '.';
            }
            //constructs a cell with the cell_layout
            // for example if cell_layout is '-' or '|' it means that this cell is part of the wall
            tmp.push_back(Cell{cell_layout, ' ', this});
            tmp.back().setCoords(i, j);
            tmp.back().attach(td);

            ++it;
        }

        grid.push_back(tmp);
    }

    // spawns all items, this MUST happen after all the cells are generated
    // or will get a segmentation fault
    for(int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++){
            FieldObject* spawned = grid[i][j].spawnLayout();
            if(spawned != nullptr) grid[i][j].setCellType('.');
        }
    }

    Map::assignDragonHoardProtection();

}

void Map::assignDragonHoardProtection(){
    for(int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j++){
            Info ci = grid[i][j].getInfo();

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Gold"){

                Gold* g = static_cast<Gold*>(ci.whatIsOccupied);

                if(g->getValue() != 6) continue;

                Map::lookforDragon(g, i, j);
            }
        }
    }
}

void Map::lookforDragon(Gold* g, int r, int c){

    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++) {

            if(grid[r + i][c + j].getIsOccupied()) {
                Info inf = grid[r + i][c + j].getInfo();

                if(inf.whatIsOccupied->getFieldIdentity() == 'D') {
                    Dragon* dr = static_cast<Dragon*>(inf.whatIsOccupied);

                    if(dr->isBusy()) continue;

                    dr->guardGold(g);
                    g->set_guard(dr);

                    return;
                }
            }
        }
    }
}

void Map::spawnStair(){

    while(true){
        //generates a random coordinate
        int randRow = rand()%ROW_NUM;
        int randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(randGridInfo.cellType == '.' && randGridInfo.chamber != playerChamber) {
           grid[randRow][randCol].setCellType('\\');
           return;
        }
    }
}

Player* Map::spawnPlayer(string playerRace){

    td->setAction(actionType::flush);

    bool foundCell = false;

    int randRow;
    int randCol;

    // playerSpawnR and playerSpawnC is by default =1
    // if it is changed then it implies that a player position was given
    // therefore no random number is generated
    if(playerSpawnR != -1 && playerSpawnC != -1) {
        foundCell = true;
        randRow = playerSpawnR;
        randCol = playerSpawnC;
    }

    // this is ascii '0' to '4'
    int chamber = 48 + rand()%4;

    while(!foundCell) {
        randRow = rand()%ROW_NUM;
        randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(    randGridInfo.isOccupied
            || randGridInfo.cellType == '|'
            || randGridInfo.cellType == '_'
            || randGridInfo.cellType == ' '
            || randGridInfo.cellType == '+'
            || randGridInfo.cellType == '#'
            || randGridInfo.cellType == '\\'
            || randGridInfo.chamber != chamber) {

        } else {
            foundCell = true;
            //sets player chamber
            playerChamber = randGridInfo.chamber;
        }

    }

    // attach the player to the text display and notify it
    p = grid[randRow][randCol].spawnPlayer(playerRace);
    p->attach(td);
    p->notifyObservers(SubscriptionType::textDisplay);
    td->setAction(actionType::spawn);

    return p;
}

void Map::spawnPlayer(Player* old_p){

    td->setAction(actionType::flush);

    bool foundCell = false;

    int randRow;
    int randCol;

    if(playerSpawnR != -1 && playerSpawnC != -1) {
        foundCell = true;
        randRow = playerSpawnR;
        randCol = playerSpawnC;
    }

    int chamber = 48 + rand()%4;

    while(!foundCell) {

        randRow = rand()%ROW_NUM;
        randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

        if(    randGridInfo.isOccupied
            || randGridInfo.cellType == '|'
            || randGridInfo.cellType == '_'
            || randGridInfo.cellType == ' '
            || randGridInfo.cellType == '+'
            || randGridInfo.cellType == '#'
            || randGridInfo.cellType == '\\'
            || randGridInfo.chamber != chamber) {

        } else {
            foundCell = true;
            //sets player chamber
            playerChamber = randGridInfo.chamber;

        }

    }

    // assign the player of the floor to the player that just came up the floor
    p = old_p;

    // Resets the player's position from the old floor
    p->setRow(randRow);
    p->setCol(randCol);

    // attach the player to the text display and notify it
    grid[randRow][randCol].spawnPlayer(p);
    p->attach(td);
    p->notifyObservers(SubscriptionType::textDisplay);
    td->setAction(actionType::newFloor);

}

void Map::spawnEnemies(int n){

    int enemiesSpawned = 0;

    while(enemiesSpawned < n){

         // generates a random chamber
        char randChamber = 48 + rand()%5;

        Info randGridInfo;
        int randRow;
        int randCol;

        do {

            //generates a random coordinate
            randRow = rand()%ROW_NUM;
            randCol = rand()%COL_NUM;

            randGridInfo = grid[randRow][randCol].getInfo();

        } while (randGridInfo.chamber != randChamber );

        //
        if(randGridInfo.isOccupied || randGridInfo.cellType == '|'
                                   || randGridInfo.cellType == '-'
                                   || randGridInfo.cellType == ' '
                                   || randGridInfo.cellType == '+'
                                   || randGridInfo.cellType == '#'
                                   || randGridInfo.cellType == '\\') {
        } else {
            // spawns an enemy in the selected grid
            enemies.push_back(grid[randRow][randCol].spawnEnemy());
            enemiesSpawned++;
        }
    }
}

void Map::spawnEnemies(){

    for(int i = 0; i < ROW_NUM; i++) {
        for(int j = 0; j < COL_NUM; j++) {
            Info ci = grid[i][j].getInfo();
            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Enemy"){
                Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);
                enemies.emplace_back(e);
            }
        }
    }

}

void Map::spawnItems(itemType t, int n){

    int itemsSpawned = 0;

    while(itemsSpawned < n) {

        //generates a random coordinate
        int randRow = rand()%ROW_NUM;
        int randCol = rand()%COL_NUM;

        Info randGridInfo = grid[randRow][randCol].getInfo();

         if( (!randGridInfo.isOccupied) && randGridInfo.cellType == '.' ){
            Item* temp = grid[randRow][randCol].spawnItem(t);
            itemsSpawned++;

            if (t == itemType::gold) {
                Gold* dh = static_cast<Gold*> (temp);
                if (dh->getValue() == 6) {
                    Map::spawnDragon(dh, randRow, randCol);
                }
            }
         }
    }
}

void Map::spawnDragon(Gold *dh, int r, int c) {
    while (true) {
        int dragonRow = rand()%3 - 1;
        int dragonCol = rand()%3 - 1;

        // make sure it won't be (0,0)
        if (dragonCol == 0 && dragonRow == 0) continue;

        // make sure it is not out of range
        if (((dragonRow + r < ROW_NUM) && (dragonCol + c < COL_NUM)) &&
            ((dragonRow + r > 0) && (dragonCol + c > 0))) {

            Info randGridInfo = grid[r+dragonRow][c+dragonCol].getInfo();
            if ((!randGridInfo.isOccupied) && randGridInfo.cellType == '.' ){
                Enemy *e = grid[r+dragonRow][c+dragonCol].spawnDragon(dh);
                Dragon *g = static_cast<Dragon*> (e);
                dh->set_guard(g);
                return;
            }
        }
    }
}

// moves the pplayer
mapState Map::movePlayer(int dx, int dy){

    td->setAction(actionType::flush);

    p->move(dx, dy);

    td->setAction(actionType::move);

    int newPlayerRow = p->getRow();
    int newPlayerCol = p->getCol();

    Info ci = grid[newPlayerRow][newPlayerCol].getInfo();
    if(ci.cellType == '\\') {
        s = mapState::win;
    }


    for(int dr = -1; dr < 2; dr++) {
        for(int dc = -1; dc < 2; dc++) {

            Info ci = grid[newPlayerRow + dr][newPlayerCol + dc].getInfo();
            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Enemy"){

                Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);
                e->attack(*p);
                td->setAction(actionType::beAttacked);

            }
        }
    }

    return s;
}

mapState Map::movePlayer(string direction){

    td->setAction(actionType::flush);

    int dx;
    int dy;

    string directionWord;

    if(direction == "no") {
        dx = -1;
        dy = 0;
        directionWord = "North";
    } else if (direction == "so") {
        dx = 1;
        dy = 0;
        directionWord = "South";
    } else if(direction == "ea") {
        dx = 0;
        dy = 1;
        directionWord = "East";
    } else if (direction == "we") {
        dx = 0;
        dy = -1;
        directionWord = "West";
    } else if (direction == "ne") {
        dx = -1;
        dy = 1;
        directionWord = "North East";
    } else if (direction == "nw") {
        dx = -1;
        dy = -1;
        directionWord = "North West";
    } else if (direction == "se") {
        dx = 1;
        dy = 1;
        directionWord = "South East";
    } else if (direction == "sw") {
        dx = 1;
        dy = -1;
        directionWord = "South West";
    } else {
        dx = 0;
        dy = 0;
    }

    int newPlayerRow = p->getRow();
    int newPlayerCol = p->getCol();

    //checks if the next cell has gold and if it can be picked up
    Info ci = grid[newPlayerRow + dx][newPlayerCol + dy].getInfo();

    if(ci.cellType == '\\') {
        s = mapState::win;
    }

    if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Gold"){
        Gold* g = static_cast<Gold*>(ci.whatIsOccupied);

        if(g->getValue() == 6 && !g->get_bool()){
             td->setAction(actionType::dragonAlive, actionInfo{0,0,' ', directionWord});
        } else {
            td->setAction(actionType::move, actionInfo{0,0,' ', directionWord});
        }
    } else {
        td->setAction(actionType::move, actionInfo{0,0,' ', directionWord});
    }

    p->move(dx, dy);
    newPlayerRow = p->getRow();
    newPlayerCol = p->getCol();

    int potionCount = 0;
    for(int dr = -1; dr < 2; dr++) {
        for(int dc = -1; dc < 2; dc++) {

            Info ci = grid[newPlayerRow + dr][newPlayerCol + dc].getInfo();

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Potion") {
                potionCount++;
            }

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Enemy"){

                Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);

                int beforeHP = p->getHP();
                e->attack(*p);
                int afterHP = p->getHP();

                char eChar = e->getFieldIdentity();

                td->setAction(actionType::beAttacked, actionInfo{beforeHP - afterHP, 0 , eChar, "", ""});
            }

            if(ci.isOccupied && ci.whatIsOccupied->objectType() == "Gold") {

                Gold *g = static_cast<Gold*>(ci.whatIsOccupied);
                if (g->getValue() == 6 && g->get_bool() == false) {
                    int beforeHP = p->getHP();
                    g->get_guard()->attack(*p);
                    int afterHP = p->getHP();
                    char eChar = g->get_guard()->getFieldIdentity();
                    td->setAction(actionType::beAttacked, actionInfo{beforeHP - afterHP, 0 , eChar, "", ""});
                }
            }
        }
    }

     // uses the damage field just because they are both int
     if(potionCount > 0) td->setAction(actionType::seePotion, actionInfo{potionCount});

     return s;

}

void Map::attack(int dx, int dy){

    td->setAction(actionType::flush);

    int r = p->getRow() + dx;
    int c = p->getCol() + dy;

    if(!grid[r][c].getIsOccupied()) return;

    Info ci = grid[r][c].getInfo();

    string ot = ci.whatIsOccupied->objectType();

    if(ot == "Enemy") {
        Enemy* e = static_cast<Enemy*>(ci.whatIsOccupied);

        int beforeHP = e->getHP();
        p->attack(*e);
        int afterHP = e->getHP();

        int damage = beforeHP - afterHP;

        char eFieldIdentity = e->getFieldIdentity();

        if(afterHP > 0) {
            td->setAction(actionType::attacked, actionInfo{damage, afterHP, eFieldIdentity, ""});
        } else {
            td->setAction(actionType::killedEnemy, actionInfo{damage, 0, eFieldIdentity, ""});
        }
    }
}

// next turn
mapState Map::nextTurn(){

    // vector<Enemy*> tmp(enemies.size());
    // auto it = copy_if(enemies.begin(), enemies.end(), tmp.begin() , [](Enemy* e) {
    //     if(e->isDead()){

    //         Info ci = e->getInfo();
    //         delete grid[ci.row][ci.col].whatIsOccupied;
    //         grid[ci.row][ci.col].unOccupy();

    //         return false;
    //     } else {
    //         return true;
    //     }
    // } );

    // tmp.resize(distance(tmp.begin(),it));
    // enemies = tmp;

    if(enemiesFrozen) return s;

    for(auto &e : enemies){

        int dx =rand()%3 - 1;
        int dy = rand()%3 - 1;

        while((dx == 0 && dy == 0)){
            dx = rand()%3 - 1;
            dy = rand()%3 - 1;
        }

        e->move(dx, dy);
    }

    return s;

}

void Map::usePotion(int dx, int dy){

    td->setAction(actionType::flush);

    int r = p->getRow() + dx;
    int c = p->getCol() + dy;

    if(!grid[r][c].getIsOccupied()) return;

    Info ci = grid[r][c].getInfo();

    string ot = ci.whatIsOccupied->objectType();
    if(ot == "Potion") {
        // the occupied object is checked to be potion, hence can be casted
        Potion* potionPtr = static_cast<Potion*>(ci.whatIsOccupied);

        string potionName = potionPtr->getName();

        // updates player stats
        p->usePotion(potionPtr);
        p->notifyObservers(SubscriptionType::textDisplay);
        td->setAction(actionType::usePotion, actionInfo{0, 0, ' ', "", potionName});
        // unoccupy the potion cell
        grid[r][c].unOccupy();
    }
}


// used when a character is killed
void Map::update(Subject &whoNotified) {

    // get the row and col of the enemy that is killed
    Info enemy_info = whoNotified.getInfo();

    // check if the character killed is a player
    if(enemy_info.cellType == '@') {
        s = mapState::playerDead;
        return;
    }

    int r = enemy_info.row;
    int c = enemy_info.col;
    string race = enemy_info.race;

    // this actually gets the pointer to the enemy, by asking the cell
    // what is occupying it
    Info ci = grid[r][c].getInfo();

    Enemy* toBeDeleted = static_cast<Enemy*>(ci.whatIsOccupied);


    grid[ci.row][ci.col].unOccupy();

    // human or merchant drops gold while other races automatilly add gold
    if(race == "human" || race == "merchant") {
        grid[ci.row][ci.col].spawnItem(itemType::gold, 4);
    }

    // when dragon dies, it gives the permission that the corresponding dragon hoard can be picked up
    if(race == "dragon") {
        Dragon* guard = static_cast<Dragon*>(toBeDeleted);
        guard->get_dh()->modi_bool();

    } else {
        p->changeGold(rand()%2 + 1);
    }

     // deletes the enemy from the list of enemies in the map
    vector<Enemy*>::iterator newEnd = std::remove(enemies.begin(), enemies.end(), toBeDeleted);
    enemies.erase(newEnd, enemies.end());

    // delete the ACTUAL enemy;
    // THE LINE BELOW CAUSES SEGMENATION FAULT
    //delete toBeDeleted;


}

void Map::freezeEnemies(){
    enemiesFrozen = !enemiesFrozen;
}

SubscriptionType Map::subType() const {
  return SubscriptionType::map;
}


// returns a pointer to the current player on map
Player* Map::getPlayerPtr(){
    return p;
}

string Map::getRawString(){
    return td->getRawString();
}

ostream &operator<<(ostream &out, const Map &m){

    if(m.td == nullptr) {
        out << "display failed to initialize";
        return out;
    }

    out << *(m.td);
    return out;
}
