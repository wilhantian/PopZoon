#ifndef _ZOO_H_
#define _ZOO_H_

#include "cocos2d.h"
#include "Prop/PropBase.h"
#include "Base/ProbabilityCalculator.h"

class Zoon;

struct ZoonPos
{
	int Row;	//行
	int Col;	//列

	ZoonPos(int _r, int _c)
	{
		Row = _r;
		Col = _c;
	}

	inline bool operator==(const ZoonPos& pos) const
	{
		return (pos.Row == Row && pos.Col == Col);
	}
};

struct ZoonPopObj
{
	int index;	// 消除队列中的第几个

	int row;	// 行
	int col;	// 列
	Zoon* zoon; // 动物
};

class Zoo : public cocos2d::Node
{
public:
	//游戏类型
	enum GameType
	{
		TIME_LIMIT,	// 限时
		STEP_LIMIT,	// 限步
		NO_LIMIT	// 不限
	};
public:
	//创建一个iRow行iCol列的动物园
	static Zoo* create(int iRow, int iCol, ProbabilityCalculator pc);

	//设置技能
	//不需要手动释放
	void	  setProp(PropBase* pProp);
	PropBase* getProp();

	//获取行列大小
	int getRowSize();
	int getColSize();

	//设置动物之间的间隔
	void setSpace(float fSpace);
	float getSpace();

	//通过行列下标过去动物
	Zoon* getZoon(int iRow, int iCol);

	//在动物园里添加/设置一个动物
	void setZoon(int iRow, int iCol, Zoon* pZoon);

	//设置游戏方式
	void setGameType(GameType gameType);

	//销毁一队列
	void popSequence(std::vector<ZoonPos> pZoons);

	//销毁一坨
	void popSpawn(std::vector<ZoonPos> pZoons);

	//销毁
	void popOnce(ZoonPos pos);

	//整理动物园
	void order();

	//检测动物园能否继续消除
	bool isCanPop();

	//获取未消除的元素大小
	//剩余大小
	int getSurplusSize();

	//获取速度
	float getSpeed();

	//下落动画
	virtual cocos2d::ActionInterval* getColAction(int iCol);

	//横向动画
	virtual cocos2d::ActionInterval* getRowAction(int iRow);


	//开始消除
	virtual void setOnPopBeginListener(const std::function<void(Zoo*)>& callback);

	//消除结束后
	virtual void setOnPopEndedListener(const std::function<void(Zoo*)>& callback);

	//一个Zoon被消除后
	virtual void setOnOnePopedListener(const std::function<void(Zoo*, ZoonPopObj zoonObj)>& callback);

	//整理完毕后
	virtual void setOnOrderBeginListener(const std::function<void(Zoo*)>& callback);

	//整理完毕后
	virtual void setOnOrderEndedListener(const std::function<void(Zoo*)>& callback);

	//用户成功点击
	virtual void setOnUserClickOkListener(const std::function<void(Zoo*, ZoonPos)>& callback);

protected:
	virtual bool init(int iRow, int iCol, ProbabilityCalculator pc);

	Zoo();

	virtual ~Zoo();

	void _addZoon(int iType, int iRow, int iCol);
	
	void _addRandomZoon(int iRow, int iCol);

	bool onTouchBenginLisener(cocos2d::Touch* touch, cocos2d::Event* eve);

	//开始消除
	virtual void onPopBegin();

	//消除结束后
	virtual void onPopEnded();

	//一个Zoon被消除后
	virtual void onOnePoped(int iRow, int iCol, Zoon* zoon);

	//整理完毕后
	virtual void onOrderBegin();

	//整理完毕后
	virtual void onOrderEnded();

protected:
	int m_iRowSize;			//行
	int m_iColSize;			//列

	float m_fWidth;			//Zoon宽
	float m_fHeight;		//Zoon高

	float m_fSpace;			//间距

	float m_fSpeed;			//下落速度

	GameType m_gameType;	//游戏类型

	std::vector<Zoon*>		m_vZoons;		//动物集合

	std::vector<ZoonPos>	m_vOpen;		//未检查的节点
	std::vector<ZoonPos>	m_vClose;		//以检查的节点

	bool					m_isPoping;		//正在消除标识
	int						m_popCount;		//消除队列计数(当前消除的计数)

	PropBase*				m_nowProp;		//当前特技(null is normal)	

	std::function<void(Zoo*)>			onPopBeginCallback;
	std::function<void(Zoo*)>			onPopEndedCallback;
	std::function<void(Zoo*, ZoonPopObj)>		onOnePopedCallback;
	std::function<void(Zoo*)>			onOrderBeginCallback;
	std::function<void(Zoo*)>			onOrderEndedCallback;

	std::function<void(Zoo*, ZoonPos)> onUserClickedOkCallback;

	ProbabilityCalculator m_pc;
	std::vector<int>	  m_pcList;
};

#endif