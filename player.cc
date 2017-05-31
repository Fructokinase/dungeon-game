#include "player.h"
#include "cell.h"
#include "gold.h"
#include "potiontype.h"
#include "potion.h"

Player::Player(Cell* spawnedIn, int x, int y): Character(spawnedIn, x ,y),
gold{0}, fieldIdentity{'@'},floorAtkBoost(0), floorDefBoost(0) {};

Player::~Player() {};

void Player::init(int defaultHp, int defaultAtt, int defaultDef) {
    Character::setStats(defaultHp, defaultAtt, defaultDef);
}

char Player::getFieldIdentity(){
    return fieldIdentity;
}

void Player::changeGold(Gold*  g){
    gold+=g->getValue();
    notifyObservers(SubscriptionType::textDisplay);
    delete g;
}

void Player::changeGold(int n){
    gold+=n;
    notifyObservers(SubscriptionType::textDisplay);
}

int Player::getGold(){
    return gold;
}

int Player::getRow(){
    return Character::posX;
}

int Player::getCol(){
    return Character::posY;
}

void Player::setRow(int r){
    Character::posX = r;
}

void Player::setCol(int c){
    Character::posY = c;
}

void Player::move(int dx, int dy){

    if(occupiedCell->canMoveTo(this, dx, dy)) {

        dettach(occupiedCell);

        occupiedCell->unOccupy();

        // changes the pointer to the cell it is occupying
        changeCell(occupiedCell->getPtrTo(dx, dy));

        // search for gold before occupying the cell;
        FieldObject* occupiedObject = occupiedCell->getInfo().whatIsOccupied;
        if(occupiedObject!= nullptr){
            Gold* goldPtr = static_cast<Gold*>(occupiedObject);
            Player::changeGold(goldPtr);
        }

        occupiedCell->occupy(this);

        attach(occupiedCell);

        posX = posX + dx;
        posY = posY + dy;

        // if the player reaches the staircase, notify the game
        if(occupiedCell->reachedStairs()){
            notifyObservers(SubscriptionType::game);
        }

    }
}

void Player::usePotion(Potion* p){

    potionType pt = p->getType();
    int value = p->getValue();

    // changes the value of fields depending on potion type
    // logs the change in atk/def
    if(pt == potionType::HP) {

        Character::hp+=value;
        if(Character::hp > Character::maxHP) Character::hp = Character::maxHP;
        if(Character::hp <= Character::minHP) Player::die();

    } else if (pt == potionType::Atk){
        Character::atk+=value;
        floorAtkBoost+=value;

        if(Character::atk < 0) {
            floorAtkBoost-=Character::atk;
            Character::atk = 0;
        }

    } else {
        Character::def+=p->getValue();
        floorDefBoost+=value;

        if(Character::def < 0) {
            floorDefBoost-=Character::def;
            Character::def = 0;
        }

    }

    delete p;
}

void Player::leaveMap(){
    dettach(occupiedCell);
    occupiedCell->unOccupy();
}

ostream &operator<<(ostream &out, const Player &p) {
    out << "Player race is " << p.objectType() << " HP: " << p.getHP() << endl;
    return out;
}

string Player::objectType() const {
    return "Player";
}

void Player::die(){
    notifyObservers(SubscriptionType::map);
}

