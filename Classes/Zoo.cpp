#include "Zoo.h"
#include "Zoon.h"
#include "PropNormal.h"
//---------------------------------------------
USING_NS_CC;
//---------------------------------------------
Zoo* Zoo::create(int iRow, int iCol)
{
	Zoo* zoo = new Zoo();
	if (zoo && zoo->init(iRow, iCol))
	{
		zoo->autorelease();
		return zoo;
	}
	CC_SAFE_DELETE(zoo);
	return NULL;
}
//---------------------------------------------
Zoo::Zoo():
m_fWidth(0),
m_fHeight(0),
m_fSpace(0),
m_isPoping(false),
m_fSpeed(0.1),
m_nowProp(NULL)
{

}
//---------------------------------------------
Zoo::~Zoo()
{

}
//---------------------------------------------
bool Zoo::init(int iRow, int iCol)
{
	if (!Node::init())
	{
		return false;
	}

	m_iRowSize = iRow;
	m_iColSize = iCol;

	m_vZoons.resize(m_iRowSize * m_iColSize);
	
	m_nowProp = PropNormal::getInstance();

	// 添加Zoon
	for (int i = 0; i < m_iColSize; i++ )
	{
		for (int j = 0; j < m_iRowSize; j++)
		{
			_addRandomZoon(j, i);
			//_addZoon(0, j, i);
		}
	}

	// 重置内容大小、锚点
	setContentSize(Size(m_fWidth * m_iRowSize, m_fHeight * m_iColSize));
	setAnchorPoint(Vec2(0.5, 0.5));

	// 监听触摸事件
	EventListenerTouchOneByOne* pTouchListener = EventListenerTouchOneByOne::create();
	pTouchListener->onTouchBegan = CC_CALLBACK_2(Zoo::onTouchBenginLisener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pTouchListener, this);

	return true;
}
//---------------------------------------------
void Zoo::_addZoon(int iType, int iRow, int iCol)
{
	Zoon* pZoon   = Zoon::create(iType);

	m_fWidth  = pZoon->getContentSize().width;
	m_fHeight = pZoon->getContentSize().height;

	pZoon->setPosition(Vec2(
		m_fWidth / 2 + m_fWidth * iRow,
		m_fHeight / 2 + m_fHeight* iCol));

	addChild(pZoon);

	m_vZoons.at(iRow + iCol * m_iRowSize) = pZoon;
}
//---------------------------------------------
void Zoo::_addRandomZoon(int iRow, int iCol)
{
	int iType = RandomHelper::random_int(0, 4);
	_addZoon(iType, iRow, iCol);
}
//---------------------------------------------
int Zoo::getRowSize()
{
	return m_iRowSize;
}
//---------------------------------------------
int Zoo::getColSize()
{
	return m_iColSize;
}
//---------------------------------------------
void Zoo::setSpace(float fSpace)
{
	m_fSpace = fSpace;

	for (int i = 0; i < m_iColSize; i++)
	{
		for (int j = 0; j < m_iRowSize; j++)
		{
			Zoon* pZoon = getZoon(j, i);
			pZoon->setPosition(pZoon->getPosition() + Vec2(fSpace * j, fSpace * i));
		}
	}

	setContentSize(Size(m_fWidth * m_iRowSize + fSpace * (m_iRowSize-1), m_fHeight * m_iColSize + fSpace * (m_iColSize-1)));
}
//---------------------------------------------
Zoon* Zoo::getZoon(int iRow, int iCol)
{
	return m_vZoons.at(iRow + m_iRowSize * iCol);
}
//---------------------------------------------
void Zoo::setZoon(int iRow, int iCol, Zoon* pZoon)
{
	m_vZoons.at(iRow + m_iRowSize * iCol) = pZoon;
}
//---------------------------------------------
std::vector<ZoonPos> Zoo::check(int iRow, int iCol)
{
	std::vector<ZoonPos> _zoons;

	if (getZoon(iRow, iCol) == NULL)
	{
		return _zoons;
	}

	m_vOpen.push_back(ZoonPos(iRow, iCol));

	while (!_checkOpenList())
	{
	}

	_zoons = m_vClose;

	m_vClose.clear();
	m_vOpen.clear();

	if (_zoons.size() < 2)
		_zoons.clear();

	return _zoons;
}
//---------------------------------------------
bool Zoo::onTouchBenginLisener(cocos2d::Touch* touch, cocos2d::Event* eve)
{
	float x = this->convertTouchToNodeSpace(touch).x;
	float y = this->convertTouchToNodeSpace(touch).y;
	
	if (x < 0 || y < 0)
		return true;

	if (x > getContentSize().width || y > getContentSize().height)
		return true;

	float feW = m_fWidth  + m_fSpace;
	float feH = m_fHeight + m_fSpace;

	int row = x / feW;
	int col = y / feH;
	
	//todo : 2015/6/17
	if (m_nowProp != NULL)
		m_nowProp->onHandle(this, row, col);
	//todo end

	//todo : row, col
	/*
	auto list = check(row, col);

	if (list.empty() || m_isPoping)	//如果list没有元素
	{
		return false;
	}

	float delay = 0.1f;

	//遍历选中的Zoon
	for (int i = 0; i < list.size(); i++)
	{
		if (i == 0)
		{
			//回调
			onPopBegin();
		}

		//依次销毁
		Sequence* seqAction = Sequence::create
			(
			DelayTime::create(i * delay),
			CallFunc::create([=]()
			{
				Zoon* zoon = getZoon(list.at(i).Row, list.at(i).Col);
				zoon->retain();
				zoon->destory();
				setZoon(list.at(i).Row, list.at(i).Col, NULL);
				
				//回调
				onOnePoped(list.at(i).Row, list.at(i).Col, zoon);
				zoon->release();
			}),
			NULL
			);

		this->runAction(seqAction);
	}

	//onAllPoped回调用
	scheduleOnce([=](float delay)
	{
		onPopEnded();

		unschedule("ScheduleWithOnAllPoped");

	}, delay * list.size(), "ScheduleWithOnAllPoped");
	*/
	return false;
}
//---------------------------------------------
bool Zoo::_checkOpenList()
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
	Zoon* pNow = getZoon(iRow, iCol);

	//上方Zoon
	if (iCol < m_iColSize - 1)
	{
		Zoon* pBuf = getZoon(iRow, iCol + 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol + 1));
	}

	//左方Zoon
	if (iRow > 0)
	{
		Zoon* pBuf = getZoon(iRow - 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow - 1, iCol));
	}

	//下方Zoon
	if (iCol > 0)
	{
		Zoon* pBuf = getZoon(iRow, iCol - 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol - 1));
	}

	//右方Zoon
	if (iRow < m_iRowSize - 1)
	{
		Zoon* pBuf = getZoon(iRow + 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow + 1, iCol));
	}

	return false;
}
//---------------------------------------------
bool Zoo::_isCloseListHave(ZoonPos pos)
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
//---------------------------------------------
bool Zoo::_isOpenListHave(ZoonPos pos)
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
//---------------------------------------------
void Zoo::_pushInOpenList(ZoonPos pos)
{
	if (!_isCloseListHave(pos) && !_isOpenListHave(pos))
	{
		m_vOpen.push_back(pos);
	}
}
//---------------------------------------------
void Zoo::order()
{
	//回调
	onOrderBegin();

	float colDelay = 0.0f;	//竖排的zoon下落完的秒数
	float rowDelay = 0.0f;	//横排的zoon下落完的秒数

	//行检测
	for (int i = 0; i < m_iRowSize; i++)
	{
		int iColCount = 0;

		for (int j = 0; j < m_iColSize; j++)
		{
			Zoon* pZoon = getZoon(i, j);

			if (pZoon == NULL)
			{
				iColCount++;
			}
			else if (iColCount > 0)
			{
				ActionInterval* action = getColAction(iColCount);
				pZoon->runAction(action);

				setZoon(i, j - iColCount, pZoon);
				setZoon(i, j, NULL);

				//累计所有延时时间
				if (colDelay < action->getDuration())
				{
					colDelay = action->getDuration();
				}
			}
		}
	}

	//列检测
	int iMoveColCount = 0;

	for (int i = 0; i < m_iRowSize; i++)
	{
		int iColCount = 0;

		for (int j = 0; j < m_iColSize; j++)
		{
			Zoon* pZoon = getZoon(i, j);
			if (pZoon == NULL)
			{
				iColCount++;
			}
			else if (iMoveColCount > 0)
			{
				Sequence* sequence = Sequence::create(
					DelayTime::create(colDelay),
					getRowAction(iMoveColCount),
					NULL);

				pZoon->runAction(sequence);
				setZoon(i - iMoveColCount, j, pZoon);
				setZoon(i, j, NULL);

				//累计所有延时时间
				if (rowDelay < sequence->getDuration())
				{
					rowDelay = sequence->getDuration();
				}
			}
		}

		//如果一列都空
		if (iColCount == m_iColSize)
		{
			iMoveColCount++;
		}
	}

	scheduleOnce([=](float del)
	{
		onOrderEnded();
		unschedule("ScheduleWithOnOrderEnded");

	}, rowDelay + colDelay, "ScheduleWithOnOrderEnded");
}
//---------------------------------------------
std::vector<ZoonPos> Zoo::checkCanPop()
{

	for (int i = 0; i < m_iColSize; i++)
	{
		for (int j = 0; j < m_iRowSize; j++)
		{
			std::vector<ZoonPos> zoons;
			zoons = check(i, j);

			if (!zoons.empty())
				return zoons;
		}
	}

	std::vector<ZoonPos> nullZoons;

	return nullZoons;
}
//---------------------------------------------
void Zoo::onPopBegin()
{
	log("onPopBegin");

	m_isPoping = true;
}
//---------------------------------------------
void Zoo::onPopEnded()
{
	log("onAllPoped");

	order();
}
//---------------------------------------------
void Zoo::onOnePoped(int iRow, int iCol, Zoon* zoon)
{
	log("onOnePoped: %d, %d, %d", iRow, iCol, zoon->getType());
}
//---------------------------------------------
void Zoo::onOrderBegin()
{
	log("onOrderBegin");
}
//---------------------------------------------
void Zoo::onOrderEnded()
{
	log("onOrderEnded");

	m_isPoping = false;

}
//---------------------------------------------
float Zoo::getSpeed()
{
	return m_fSpeed;
}
//---------------------------------------------
ActionInterval* Zoo::getColAction(int iCol)
{
	MoveBy* moveDownFirst	= MoveBy::create(m_fSpeed * iCol, Vec2(0, -(m_fHeight + m_fSpace)*iCol));
	MoveBy* moveDownSecond	= MoveBy::create(0.1, Vec2(0, -m_fSpace));
	MoveBy* moveBack		= MoveBy::create(0.1, Vec2(0, m_fSpace*2));
	MoveBy* moveBackThird	= MoveBy::create(0.1, Vec2(0, -m_fSpace));

	Sequence* sequence = Sequence::create(
		moveDownFirst,
		moveDownSecond,
		moveBack,
		moveBackThird,
		NULL);

	return sequence;
}
//---------------------------------------------
ActionInterval* Zoo::getRowAction(int iRow)
{
	MoveBy* moveDownFirst	= MoveBy::create(m_fSpeed * iRow, Vec2(-(m_fHeight + m_fSpace)*iRow, 0));
	MoveBy* moveDownSecond	= MoveBy::create(0.1, Vec2(-m_fSpace, 0));
	MoveBy* moveBack		= MoveBy::create(0.1, Vec2(m_fSpace * 2, 0));
	MoveBy* moveBackThird	= MoveBy::create(0.1, Vec2(-m_fSpace, 0));

	Sequence* sequence = Sequence::create(
		moveDownFirst,
		moveDownSecond,
		moveBack,
		moveBackThird,
		NULL);

	return sequence;
}
//---------------------------------------------