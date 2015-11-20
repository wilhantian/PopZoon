#include "Zoo.h"
#include "Zoon.h"
#include "Prop/PropNormal.h"
#include "Prop/PropBomb.h"
#include "Event/MsgEvent.h"
#include "GameManager/AchievementSystem.h"
//---------------------------------------------
USING_NS_CC;
//---------------------------------------------
Zoo* Zoo::create(int iRow, int iCol, ProbabilityCalculator pc)
{
	Zoo* zoo = new Zoo();
	if (zoo && zoo->init(iRow, iCol, pc))
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
m_nowProp(NULL),
m_gameType(Zoo::GameType::NO_LIMIT),
m_popCount(0),
onPopBeginCallback(nullptr),
onPopEndedCallback(nullptr),
onOnePopedCallback(nullptr),
onOrderBeginCallback(nullptr),
onOrderEndedCallback(nullptr),
onUserClickedOkCallback(nullptr)
{

}
//---------------------------------------------
Zoo::~Zoo()
{
	CC_SAFE_DELETE(m_nowProp);
}
//---------------------------------------------
bool Zoo::init(int iRow, int iCol, ProbabilityCalculator pc)
{
	if (!Node::init())
	{
		return false;
	}

	m_iRowSize = iRow;
	m_iColSize = iCol;
	m_pc = pc;

	m_vZoons.resize(m_iRowSize * m_iColSize);
	
	// 初始化道具
	setProp(new PropNormal());
	//setProp(new PropBomb());

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
void Zoo::setProp(PropBase* pProp)
{
	if (m_nowProp)
	{
		m_nowProp->release();
	}

	m_nowProp = pProp;
}
//---------------------------------------------
PropBase* Zoo::getProp()
{
	return m_nowProp;
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
	
	pZoon->setPosition(pZoon->getPosition() + Vec2(m_fSpace * iRow, m_fSpace * iCol));

	addChild(pZoon);

	m_vZoons.at(iRow + iCol * m_iRowSize) = pZoon;
}
//---------------------------------------------
void Zoo::_addRandomZoon(int iRow, int iCol)
{
	if (m_pcList.empty())
	{
		m_pcList = m_pc.getEventList(m_iColSize * m_iRowSize);
	}

	int iType = m_pcList.at(m_pcList.size()-1);
	m_pcList.pop_back();
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
float Zoo::getSpace()
{
	return m_fSpace;
}
//---------------------------------------------
Zoon* Zoo::getZoon(int iRow, int iCol)
{
	if (iRow < 0 || iCol < 0)
		return NULL;

	if (iRow + 1 > m_iRowSize || iCol + 1 > m_iColSize)
		return NULL;

	return m_vZoons.at(iRow + m_iRowSize * iCol);
}
//---------------------------------------------
void Zoo::setZoon(int iRow, int iCol, Zoon* pZoon)
{
	m_vZoons.at(iRow + m_iRowSize * iCol) = pZoon;
}
//---------------------------------------------
void Zoo::setGameType(GameType gameType)
{
	m_gameType = gameType;
}
//---------------------------------------------
void Zoo::popSequence(std::vector<ZoonPos> pZoons)
{
	if (pZoons.empty() || m_isPoping)	//如果list没有元素
		return;

	float delay = 0.1f;

	//遍历选中的Zoon
	for (int i = 0; i < pZoons.size(); i++)
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
				popOnce(pZoons.at(i));
			}),
			NULL
		);

		runAction(seqAction);
	}

	//onAllPoped回调用
	scheduleOnce([=](float delay)
	{
		onPopEnded();
		order();

	}, delay * pZoons.size(), "ScheduleWithOnAllPoped");
}
//---------------------------------------------
void Zoo::popSpawn(std::vector<ZoonPos> pZoons)
{
	if (pZoons.empty() || m_isPoping)	//如果list没有元素
		return;

	float delay = 0.5f;

	//遍历选中的Zoon
	for (int i = 0; i < pZoons.size(); i++)
	{
		if (i == 0)
		{
			//回调
			onPopBegin();
		}

		//依次销毁
		popOnce(pZoons.at(i));
	}

	//onAllPoped回调用
	scheduleOnce([=](float delay)
	{
		onPopEnded();
		order();

	}, delay, "ScheduleWithOnAllPopedEx");
}
//---------------------------------------------
void Zoo::popOnce(ZoonPos pos)
{

	Zoon* zoon = getZoon(pos.Row, pos.Col);
	
	//回调
	onOnePoped(pos.Row, pos.Col, zoon);

	zoon->retain();
	zoon->destory();
	setZoon(pos.Row, pos.Col, NULL);

	zoon->release();

	//--------------------------
	// test 涌动
	Zoon* pLeftZoon = getZoon(pos.Row - 1, pos.Col); 
	Zoon* pRightZoon = getZoon(pos.Row + 1, pos.Col);
	Zoon* pUpZoon = getZoon(pos.Row, pos.Col + 1);
	Zoon* pDownZoon = getZoon(pos.Row, pos.Col - 1);

	if (pLeftZoon)
		pLeftZoon->swarmForLeft(this->getSpace());
	if (pRightZoon)
		pRightZoon->swarmForRight(this->getSpace());
	if (pUpZoon)
		pUpZoon->swarmForUp(this->getSpace());
	if (pDownZoon)
		pDownZoon->swarmForDown(this->getSpace());
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
	
	bool isPopOk = false;	// 是否成功处理

	//todo : 2015/6/17
	//技能
	if (m_nowProp != NULL)
	{
		isPopOk = m_nowProp->onHandle(this, row, col);
	}
	//todo end
	
	if (onUserClickedOkCallback && isPopOk)
	{
		ZoonPos zPos(row, col);
		onUserClickedOkCallback(this, zPos);
	}
	
	if (!isPopOk)
	{
		// 成就计数
		AchievementSystem::getInstance()->triggerClickFailZoonOnce();
	}

	return false;
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
		if (m_gameType == GameType::TIME_LIMIT)
		{
			// 创造新的动物
			for (int i = 0; i < m_iRowSize; i++)
			{
				for (int j = 0; j < m_iColSize; j++)
				{
					// 如果为空，那么创造新的公动物
					if (getZoon(i, j) == NULL)
					{
						_addRandomZoon(i, j);
					}
				}
			}
		}

		onOrderEnded();

	}, rowDelay + colDelay - 0.1, "ScheduleWithOnOrderEnded");
}
//---------------------------------------------
bool Zoo::isCanPop()
{
	//获取可以消除的一组
// 	for (int i = 0; i < m_iColSize; i++)
// 	{
// 		for (int j = 0; j < m_iRowSize; j++)
// 		{
// 			std::vector<ZoonPos> zoons;
// 			zoons = check(i, j);
// 
// 			if (!zoons.empty())
// 				return zoons;
// 		}
// 	}
// 
// 	std::vector<ZoonPos> nullZoons;
// 
// 	return nullZoons;

	for (int i = 0; i < m_iColSize - 1; i++)
	{
		for (int j = 0; j < m_iRowSize - 1; j++)
		{
			Zoon* c1 = getZoon(i, j  );
			Zoon* c2 = getZoon(i, j+1);

			if (c1 && c2 && c1->getType() == c2->getType())
				return true;

			Zoon* r1 = getZoon(i    , j);
			Zoon* r2 = getZoon(i + 1, j);

			if (r1 && r2 && r1->getType() == r2->getType())
				return true;
		}
	}

	return false;
}
//---------------------------------------------
void Zoo::onPopBegin()
{
	if (onPopBeginCallback)
	{
		onPopBeginCallback(this);
	}

	m_isPoping = true;
}
//---------------------------------------------
void Zoo::onPopEnded()
{
	if (onPopEndedCallback)
	{
		onPopEndedCallback(this);
	}
}
//---------------------------------------------
void Zoo::onOnePoped(int iRow, int iCol, Zoon* zoon)
{
	ZoonPopObj zoonObj;
	zoonObj.index = m_popCount;
	zoonObj.row   = iRow;
	zoonObj.col   = iCol;
	zoonObj.zoon  = zoon;

	if (onOnePopedCallback)
	{
		onOnePopedCallback(this, zoonObj);
	}

	m_popCount++;
}
//---------------------------------------------
void Zoo::onOrderBegin()
{
	if (onOrderBeginCallback)
	{
		onOrderBeginCallback(this);
	}
}
//---------------------------------------------
void Zoo::onOrderEnded()
{
	if (onOrderEndedCallback)
	{
		onOrderEndedCallback(this);
	}

	m_isPoping = false;
	m_popCount = 0;
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
void Zoo::setOnPopBeginListener(const std::function<void(Zoo*)>& callback)
{
	onPopBeginCallback = callback;
}
//---------------------------------------------
void Zoo::setOnPopEndedListener(const std::function<void(Zoo*)>& callback)
{
	onPopEndedCallback = callback;
}
//---------------------------------------------
void Zoo::setOnOnePopedListener(const std::function<void(Zoo*, ZoonPopObj zoonObj)>& callback)
{
	onOnePopedCallback = callback;
}
//---------------------------------------------
void Zoo::setOnOrderBeginListener(const std::function<void(Zoo*)>& callback)
{
	onOrderBeginCallback = callback;
}
//---------------------------------------------
void Zoo::setOnOrderEndedListener(const std::function<void(Zoo*)>& callback)
{
	onOrderEndedCallback = callback;
}
//---------------------------------------------
void Zoo::setOnUserClickOkListener(const std::function<void(Zoo*, ZoonPos)>& callback)
{
	onUserClickedOkCallback = callback;
}
//---------------------------------------------
int Zoo::getSurplusSize()
{
	int count = 0;

	for (int i = 0; i < m_iRowSize; i++)
	{
		for  (int j = 0; j < m_iColSize; j++)
		{
			Zoon* pZoon = getZoon(m_iRowSize, m_iColSize);
			if (pZoon)
			{
				count++;
			}
		}
	}

	return count;
}
//---------------------------------------------