#include <iostream>
#include <utility>
#include "textdisplay.h"
#include "cellinfo.h"
#include "cell.h" // why??
#include "fieldobject.h"
#include "player.h"

using namespace std;

TextDisplay::TextDisplay(int r, int c, int f, string& map_layout): ROW_NUM(r), COL_NUM(c), floorN(f){

    string::iterator it=map_layout.begin(); 

    for(int i = 0; i < ROW_NUM; i++){
        vector<char> tmp;
        for(int j = 0; j < COL_NUM; j++) {
            tmp.push_back(*it);
            it++;
        }
        theDisplay.push_back(tmp);
    }

    enemy['H'] = "Human";
    enemy['W'] = "Dwarf";
    enemy['L'] = "Halfling";
    enemy['E'] = "Elf";
    enemy['O'] = "Orc";
    enemy['M'] = "Merchant";
    enemy['D'] = "Dragon";
}

TextDisplay::~TextDisplay() {}

// udpate when c
void TextDisplay::update(Subject &whoNotified) {

    Info ci = whoNotified.getInfo();

    if(ci.row == -1){
        playerRace = ci.race;
        playerHP = ci.hp;
        playerAtk = ci.atk;
        playerDef = ci.def;
        playerGold = ci.gold;
        return;
    }
    // If a cell is occupied, display what is occupying it by asking
    // the occupied object directly what it should display
    // or else it displays the cellType (map)
    if(ci.isOccupied){
        theDisplay[ci.row][ci.col] = (ci.whatIsOccupied)->getFieldIdentity();
    } else {
        theDisplay[ci.row][ci.col] = ci.cellType;
    }

}

void TextDisplay::setAction(actionType at){

    if(at == actionType::flush) {
        action = "";
        return;
    }

    if(at == actionType::newFloor) {
        action.append("Player character reached new floor. ");
        return;
    }

    if(at == actionType::spawn) {
        action.append("Player character has spawned. ");
        return;
    } 

}

void TextDisplay::setAction(actionType at, actionInfo ai){

    if(at == actionType::move){
        action.append("PC moves ");
        action.append(ai.direction);
        action.append(". ");
        return;
    }

    if(at == actionType::attacked) {
        action.append("PC deals ");
        action.append(to_string(ai.damage));
        action.append(" damage to ");
        action.append(enemy[ai.fieldIdentity]);
        action.append("(");
        action.append(to_string(ai.hp));
        action.append(" HP). ");
        return;
    }

    if(at == actionType::killedEnemy) {
        action.append("PC deals ");
        action.append(to_string(ai.damage));
        action.append(" damage to ");
        action.append(enemy[ai.fieldIdentity]);
        action.append(" and killed it.");
        return;
    }

    if(at == actionType::beAttacked) {
        action.append(enemy[ai.fieldIdentity]);
        action.append(" deals ");
        action.append(to_string(ai.damage));
        action.append(" damage to PC. ");
        return;
    }

    if (at == actionType::seePotion) {

        if (ai.damage == 1) {
            action.append("PC saw an unknown potion. ");
            return;
        }

        action.append("PC saw ");
        action.append(to_string(ai.damage));
        action.append(" unknown potions.");
        return;
    }

    if(at == actionType::usePotion) {
        action.append("PC uses ");
        action.append(ai.itemType);
        action.append(".");
        return;
    }

    if(at == actionType::dragonAlive){
        action.append("PC attempts to move ");
        action.append(ai.direction);
        action.append(" towards a Dragon Hoard but the guardian dragon is still alive.");
        return;
    }

}

SubscriptionType TextDisplay::subType() const {
  return SubscriptionType::textDisplay;
}

string TextDisplay::getRawString(){

    string result = "";
    for (int i = 0; i < ROW_NUM; i++) {
        for (int j = 0; j < COL_NUM; j ++) {
            result+=theDisplay[i][j];
        }
    }

    result.append("Race: ");
    result.append(playerRace);
    result.append(" Gold: ");
    result.append(to_string(playerGold));
    result.append(" Floor ");
    result.append(to_string(floorN));
    result.append("HP: " + to_string(playerHP) + "\n");
    result.append("Atk: " + to_string(playerAtk) + "\n");
    result.append("Def: " +  to_string(playerDef) + "\n");
    result.append("Action: " +  action + "\n");

    return result;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {


    // for the game board
    for (int i = 0; i < td.ROW_NUM; i++) {
        for (int j = 0; j < td.COL_NUM; j ++) {
            out  << td.theDisplay[i][j];
        }
        out << endl;
    }

    // for the player status
    out << "Race: " << td.playerRace  << " Gold: " << td.playerGold;
    out.width(57);
    out << "Floor " << td.floorN << endl;

    out << "HP: " << td.playerHP << endl;
    out << "Atk: " << td.playerAtk << endl;
    out << "Def: " << td.playerDef << endl;
    out << "Action: " << td.action << endl;

    return out;
}
