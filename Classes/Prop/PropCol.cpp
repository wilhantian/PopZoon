//
//  PropCol.cpp
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/16.
//
//
//---------------------------------------------------
#include "PropCol.h"
#include "View/Zoo.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
bool PropCol::onHandle(Zoo* pZoo, int iRow, int iCol)
{
    if (pZoo->getZoon(iRow, iCol) == NULL)
        return false;
    
    int rowSize = pZoo->getRowSize();
    std::vector<ZoonPos> pZoons;
    
    for (int i=0; i<rowSize; i++)
    {
        pZoons.push_back(ZoonPos(iRow, i));
    }
    pZoo->popSequence(pZoons);
    
    return true;
}
//---------------------------------------------------