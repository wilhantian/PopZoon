//
//  PropCol.h
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/16.
//
//  纵向消除一列

#ifndef PropCol_h
#define PropCol_h

#include "cocos2d.h"
#include "PropBase.h"

class PropCol : public PropBase
{
public:
    virtual bool onHandle(Zoo* pZoo, int iRow, int iCol);
};

#endif /* PropCol_h */
