//
//  HUDLayer.h
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/10/27.
//
//

#ifndef HUDLayer_h
#define HUDLayer_h

#include "cocos2d.h"

enum PropType{
    PropType_Row = 100,     // 行消除
    PropType_Col,           // 列消除
    PropType_Bomb,          // 炸弹
    PropType_Sinker,        // 锤子
    PropType_Move,          // 乾坤大挪移
};

class HUDLayer : public cocos2d::Layer
{
public:
    CREATE_FUNC(HUDLayer);
    
    void onPropButtonClick(Ref* pSender);
    
protected:
    virtual bool init();
};

#endif /* HUDLayer_h */
