#ifndef _ZOO_H_
#define _ZOO_H_

#include "cocos2d.h"
#include "PropBase.h"

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


class Zoo : public cocos2d::Node
{
public:
	//创建一个iRow行iCol列的动物园
	static Zoo* create(int iRow, int iCol);

	//获取行列大小
	int getRowSize();
	int getColSize();

	//设置动物之间的间隔
	void setSpace(float fSpace);

	//通过行列下标过去动物
	Zoon* getZoon(int iRow, int iCol);

	//在动物园里添加/设置一个动物
	void setZoon(int iRow, int iCol, Zoon* pZoon);

	//返回相连动物
	std::vector<ZoonPos> check(int iRow, int iCol);

	//整理动物园
	void order();

	//检测动物园能否继续消除
	std::vector<ZoonPos> checkCanPop();

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

	//获取速度
	float getSpeed();

	//下落动画
	virtual cocos2d::ActionInterval* getColAction(int iCol);

	//横向动画
	virtual cocos2d::ActionInterval* getRowAction(int iRow);

protected:
	virtual bool init(int iRow, int iCol);

	Zoo();

	virtual ~Zoo();

	void _addZoon(int iType, int iRow, int iCol);
	
	void _addRandomZoon(int iRow, int iCol);

	bool onTouchBenginLisener(cocos2d::Touch* touch, cocos2d::Event* eve);

	//检查四周
	//@return 是否检查完成，open表中不在有值
	bool _checkOpenList();

	//检查闭表中是否有这个元素
	bool _isCloseListHave(ZoonPos pos);

	//检查Open表中是否有这个元素
	bool _isOpenListHave(ZoonPos pos);

	//放入Open表中
	//如果闭表中有该元素，那么不会放入这个元素
	void _pushInOpenList(ZoonPos pos);

protected:
	int m_iRowSize;			//行
	int m_iColSize;			//列

	float m_fWidth;			//Zoon宽
	float m_fHeight;		//Zoon高

	float m_fSpace;			//间距

	float m_fSpeed;			//下落速度

	std::vector<Zoon*>		m_vZoons;		//动物集合

	std::vector<ZoonPos>	m_vOpen;		//未检查的节点
	std::vector<ZoonPos>	m_vClose;		//以检查的节点

	bool m_isPoping;		//正在消除标识

	PropBase*				m_nowProp;		//now prop(null is normal)
};

#endif