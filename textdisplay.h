#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include <string>
#include "actiontype.h"
#include "actioninfo.h"
#include <map>
class Cell;

using namespace std;

class TextDisplay: public Observer {
  
  vector<std::vector<char>> theDisplay;
  const int ROW_NUM;
  const int COL_NUM;

  string playerRace;
  int playerHP;
  int playerAtk;
  int playerDef;
  int playerGold;

  int floorN = 1;

  string action;

  map<char, string> enemy;

 public:
  TextDisplay(int r, int c, int f, string& map_layout);
  ~TextDisplay();

  void update(Subject &whoNotified) override;

  void setAction(actionType at);
  void setAction(actionType at, actionInfo ai);
  string getRawString();

  SubscriptionType subType() const override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
