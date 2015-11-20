/**************************************************************************
 * Copyright (c) 2015, pxbomb, All rights reserved.
 
 * File		: RES.h
 * Date		: 2015/08/06 17:40
 * Author	: WilhanTian
 * Email	: wilhan.tian@gmail.com
 * Depict	: 资源定义
              所有的资源路径均在此处定义, 便于游戏预加载和修改对应资源
 **************************************************************************/
#ifndef _RES_H_
#define _RES_H_

#include "cocos2d.h"
#include "json/document.h"

#define ST(_KEY_) RES::Text::getInstance()->getText(##_KEY_##)

namespace RES
{
    class Text
    {
    public:
        static Text* getInstance();
        static void  destoryInstance();
        
        bool initText();
        std::string getText(std::string key);
        
    protected:
        rapidjson::Document _doc;
        
        static RES::Text* m_text;
    };
    
    //-------------------------------------------------------
    // LOGO
    const std::string LOGO = "HomeScene/Logo.png";
    
    // 开始按钮
    const std::string START_BUTTON = "HomeScene/Start.png";
    const std::string START_BUTTON1 = "HomeScene/Start1.png";
    
    // 皮肤按钮
    const std::string SKIN_BUTTON = "HomeScene/Skin.png";
    const std::string SKIN_BUTTON1 = "HomeScene/Skin1.png";
    
    // 关于按钮
    const std::string ABOUT_BUTTON = "HomeScene/About.png";
    const std::string ABOUT_BUTTON1 = "HomeScene/About1.png";
    
    // 光
    const std::string LIGHT = "HomeScene/Light.png";
    
    // 云
    const std::string CLOUD1 = "HomeScene/Cloud1.png";
    const std::string CLOUD2 = "HomeScene/Cloud2.png";
    const std::string CLOUD3 = "HomeScene/Cloud3.png";
    
    // 大云
    const std::string BIG_CLOUD1 = "HomeScene/BigCloud1.png";
    const std::string BIG_CLOUD2 = "HomeScene/BigCloud2.png";
    const std::string BIG_CLOUD3 = "HomeScene/BigCloud3.png";
    
    // 熊猫
    const std::string HOMESCENE_PANDA  = "HomeScene/Panda.png";
    const std::string HOMESCENE_RABBIT = "HomeScene/rabbit.png";
    const std::string HOMESCENE_SNAKE = "HomeScene/snake.png";
    const std::string HOMESCENE_ELEPHANT = "HomeScene/elephant.png";
    const std::string HOMESCENE_GIRAFFE = "HomeScene/giraffe.png";
    const std::string HOMESCENE_HIPPO = "HomeScene/hippo.png";
    
    //-------------------------------------------------------
    // 皮肤背景
    const std::string SKIN_PLANE = "HomeScene/SkinPlane.png";
    
    // 左选按钮
    const std::string SKIN_LEFT_BUTTON  = "HomeScene/SkinLeft.png";
    const std::string SKIN_LEFT_BUTTON1 = "HomeScene/SkinLeft1.png";
    
    // 向右按钮
    const std::string SKIN_RIGHT_BUTTON  = "HomeScene/SkinRight.png";
    const std::string SKIN_RIGHT_BUTTON1 = "HomeScene/SkinRight1.png";
    
    // 下载按钮
    const std::string SKIN_DOWN_BUTTON  = "HomeScene/SkinDown.png";
    const std::string SKIN_DOWN_BUTTON1 = "HomeScene/SkinDown1.png";
    
    // 关闭按钮
    const std::string SKIN_CLOSE  = "HomeScene/Close.png";
    const std::string SKIN_CLOSE1 = "HomeScene/Close1.png";
    
    //-------------------------------------------------------
    // 确认对话框
    const std::string DIALOG_OK		= "View/DialogView/ok.png";
    const std::string DIALOG_PLANE  = "View/DialogView/plane.png";
    
}

#endif // _RES_H_/