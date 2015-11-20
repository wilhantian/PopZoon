//
//  PropSinker.cpp
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/16.
//
//
//---------------------------------------------------
#include "PropSinker.h"
#include "View/Zoo.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
bool PropSinker::onHandle(Zoo* pZoo, int iRow, int iCol)
{
    if (pZoo->getZoon(iRow, iCol) == NULL)
        return false;
    
    ZoonPos pos(iRow, iCol);
    pZoo->popOnce(pos);
    
    return true;
}
//---------------------------------------------------