#include "PropBomb.h"
#include "View/Zoo.h"
#include "View/Zoon.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
bool PropBomb::onHandle(Zoo* pZoo, int iRow, int iCol)
{
	if (pZoo->getZoon(iRow, iCol) == NULL)
		return false;

	std::vector<ZoonPos> pZoons;
	{
		if (pZoo->getZoon(iRow + 1, iCol + 1))
			pZoons.push_back(ZoonPos(iRow+1, iCol+1));
		if (pZoo->getZoon(iRow + 1, iCol))
			pZoons.push_back(ZoonPos(iRow+1, iCol));
		if (pZoo->getZoon(iRow + 1, iCol - 1))
			pZoons.push_back(ZoonPos(iRow+1, iCol-1));
		if (pZoo->getZoon(iRow - 1, iCol + 1))
			pZoons.push_back(ZoonPos(iRow-1, iCol+1));
		if (pZoo->getZoon(iRow - 1, iCol))
			pZoons.push_back(ZoonPos(iRow-1, iCol));
		if (pZoo->getZoon(iRow - 1, iCol - 1))
			pZoons.push_back(ZoonPos(iRow-1, iCol-1));
		if (pZoo->getZoon(iRow, iCol + 1))
			pZoons.push_back(ZoonPos(iRow, iCol+1));
		if (pZoo->getZoon(iRow, iCol))
			pZoons.push_back(ZoonPos(iRow, iCol));
		if (pZoo->getZoon(iRow, iCol - 1))
			pZoons.push_back(ZoonPos(iRow, iCol-1));
	}
	pZoo->popSpawn(pZoons);


	return true;
}
//---------------------------------------------------