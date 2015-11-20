//
//  PropRow.h
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/15.
//
//  横向消除一行

#ifndef PropRow_h
#define PropRow_h

#include "cocos2d.h"
#include "PropBase.h"

class PropRow : public PropBase
{
public:
    virtual bool onHandle(Zoo* pZoo, int iRow, int iCol);
};

#endif /* PropRow_h */
