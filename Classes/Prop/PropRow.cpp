//
//  PropRow.cpp
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/11/15.
//
//
//---------------------------------------------------
#include "PropRow.h"
#include "View/Zoo.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
bool PropRow::onHandle(Zoo* pZoo, int iRow, int iCol)
{
    if (pZoo->getZoon(iRow, iCol) == NULL)
        return false;
    
    int colSize = pZoo->getColSize();
    std::vector<ZoonPos> pZoons;
    
    for (int i=0; i<colSize; i++)
    {
        pZoons.push_back(ZoonPos(i, iCol));
    }
    pZoo->popSequence(pZoons);
    
    return true;
}
//---------------------------------------------------