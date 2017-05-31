#ifndef __FIELDOBJECT_H__
#define __FIELDOBJECT_H__

#include <string>
using namespace std;

class FieldObject{
protected:
    //int spawnRow;
    //int spawnCol;

    //char fieldIdentity;

public:
    virtual char getFieldIdentity() =0;
    virtual string objectType() const =0;
    //void die();
};

#endif
