#include "subject.h"
#include "cellinfo.h"
#include "subscriptions.h"
#include <cstdlib>

using namespace std;

class MockSubject: public Subject {
    Info inf;
public:
    MockSubject(){
        inf = Info{rand()%25, rand()%79, false, '$'};
    };
    ~MockSubject(){};


    void mockNotify(){
        notifyObservers(SubscriptionType::textDisplay);
    }

    Info getInfo() const override {
        return inf;
    }


    void setInfo(){
        inf = Info{rand()%25, rand()%79, false, '$'};
        mockNotify();
    }

};
