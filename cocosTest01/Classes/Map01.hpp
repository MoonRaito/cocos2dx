//
//  Map01.hpp
//  cocosTest01
//
//  Created by Moon on 15/10/21.
//
//

#ifndef Map01_hpp
#define Map01_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class Map01:public Layer{
private:
    Sprite* bgSprite;
    Vec2 bgOrigin;
public:
    virtual bool init();
    static Scene *createScene();
    CREATE_FUNC(Map01);
    
    
    
    
    
//    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};

#endif /* Map01_hpp */
