#include "subject.h"
#include "observer.h"
#include "subscriptions.h"
#include <iostream>
#include <algorithm>

using namespace std;

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::dettach(Observer *o) {

    vector<Observer*>::iterator newEnd = std::remove(observers.begin(), observers.end(), o);
    observers.erase(newEnd, observers.end());

}


void Subject::notifyObservers(SubscriptionType t) {
    for(auto ob: observers){
        if(ob->subType() == t) {
            Subject& current = *this;
            ob->update(current);
        }
    }
}

