//
//  PropSinker.h
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/16.
//
//  锤子: 消除一个

#ifndef PropSinker_h
#define PropSinker_h

#include "cocos2d.h"
#include "PropBase.h"

class PropSinker : public PropBase
{
public:
	virtual bool onHandle(Zoo* pZoo, int iRow, int iCol);
};

#endif /* PropSinker_h */
