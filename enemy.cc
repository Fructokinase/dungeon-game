#include "enemy.h"
#include "cell.h"
#include "subscriptions.h"

using namespace std;

Enemy::Enemy(Cell* spawnedIn, int x, int y):Character(spawnedIn, x, y) {};

Enemy::~Enemy() {};

char Enemy::getFieldIdentity(){
    return 'X';
}

void Enemy::beAttackedBy(Admin&){
    Enemy::die();
}

void Enemy::move(int dx, int dy){

    // enemy move restriction
    // limits enemy movement to the 3 x 3 grid centering where they spawned
    if ( (posX + dx) <  spawnedX - 1  || (posX + dx) > spawnedX + 1 ) dx*=-1;
    if ( (posY + dy) <  spawnedY - 1  || (posY + dy) > spawnedY + 1 ) dy*=-1;

    if(occupiedCell->canMoveTo(this, dx, dy)) {

        dettach(occupiedCell);

        occupiedCell->unOccupy();

        occupiedCell = occupiedCell->getPtrTo(dx, dy);

        occupiedCell->occupy(this);

        attach(occupiedCell);

        posX = posX + dx;
        posY = posY + dy;

    }
}

void Enemy::die(){
    notifyObservers(SubscriptionType::map);
}

string Enemy::objectType() const {
    return "Enemy";
}
