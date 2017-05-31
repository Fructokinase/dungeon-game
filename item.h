#ifndef __ITEM_H__
#define __ITEM_H__

#include "fieldobject.h"
#include "itemtype.h"

class Item : public FieldObject {
protected:
    itemType t;

public:
    virtual ~Item(){};
};

#endif
