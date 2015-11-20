#include "PropNormal.h"
#include "View/Zoon.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
PropNormal* PropNormal::s_instance = NULL;
//---------------------------------------------------
PropNormal* PropNormal::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new PropNormal();
	}
	return s_instance;
}
//---------------------------------------------------
bool PropNormal::onHandle(Zoo* pZoo, int iRow, int iCol)
{
	auto list = check(pZoo, iRow, iCol);

	pZoo->popSequence(list);

	return !list.empty();
}
//---------------------------------------------------
std::vector<ZoonPos> PropNormal::check(Zoo* pZoo, int iRow, int iCol)
{
	std::vector<ZoonPos> _zoons;

	if (pZoo->getZoon(iRow, iCol) == NULL)
	{
		return _zoons;
	}

	m_vOpen.push_back(ZoonPos(iRow, iCol));

	while (!_checkOpenList(pZoo))
	{
	}

	_zoons = m_vClose;

	m_vClose.clear();
	m_vOpen.clear();

	if (_zoons.size() < 2)
		_zoons.clear();

	return _zoons;
}
//---------------------------------------------------
bool PropNormal::_checkOpenList(Zoo* pZoo)
{
	if (m_vOpen.empty())
	{
		return true;
	}

	//获取最后一个
	ZoonPos nowPos = m_vOpen.back();
	int iRow = nowPos.Row;
	int iCol = nowPos.Col;

	//放入闭表
	m_vClose.push_back(nowPos);

	//删除最后一个
	m_vOpen.pop_back();

	//当前Zoon
	Zoon* pNow = pZoo->getZoon(iRow, iCol);

	//上方Zoon
	if (iCol < pZoo->getColSize() - 1)
	{
		Zoon* pBuf = pZoo->getZoon(iRow, iCol + 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol + 1));
	}

	//左方Zoon
	if (iRow > 0)
	{
		Zoon* pBuf = pZoo->getZoon(iRow - 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow - 1, iCol));
	}

	//下方Zoon
	if (iCol > 0)
	{
		Zoon* pBuf = pZoo->getZoon(iRow, iCol - 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol - 1));
	}

	//右方Zoon
	if (iRow < pZoo->getRowSize() - 1)
	{
		Zoon* pBuf = pZoo->getZoon(iRow + 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow + 1, iCol));
	}

	return false;
}
//---------------------------------------------------
bool PropNormal::_isCloseListHave(ZoonPos pos)
{
	for (int i = 0; i < m_vClose.size(); i++)
	{
		if (m_vClose.at(i) == pos)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------
bool PropNormal::_isOpenListHave(ZoonPos pos)
{
	for (int i = 0; i < m_vOpen.size(); i++)
	{
		if (m_vOpen.at(i) == pos)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------
void PropNormal::_pushInOpenList(ZoonPos pos)
{
	if (!_isCloseListHave(pos) && !_isOpenListHave(pos))
	{
		m_vOpen.push_back(pos);
	}
}
//---------------------------------------------------