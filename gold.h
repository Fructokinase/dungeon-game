#ifndef __GOLD_H__
#define __GOLD_H__

#include "itemtype.h"
#include "item.h"

class Dragon;

class Gold : public Item {
protected:
    itemType t;
    int value;
    bool can_be_picked;
    Dragon* guard;

public:
    Gold(int);
    ~Gold();

    void modi_bool();

    bool get_bool();

    void set_guard(Dragon*);

    Dragon *get_guard();

    int getValue();

    char getFieldIdentity() override;

    string objectType() const override;
};

#endif
