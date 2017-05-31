#ifndef __ITEMFACOTRY_H_
#define __ITEMFACOTRY_H_

#include "gold.h"
#include "potion.h"
#include "itemtype.h"
#include "potiontype.h"

Item* ItemFactory(itemType t);

Item* ItemFactory(itemType t, int value);

Item* ItemFactory(potionType p, int value);

#endif
