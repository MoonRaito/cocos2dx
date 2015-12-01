//
//  Game01.hpp
//  cocosTest01
//
//  Created by Moon on 15/11/30.
//
//

#ifndef Game01_hpp
#define Game01_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class Game01:public Layer{
private:
    Sprite* bgSprite;
    Vec2 bgOrigin;
    Layer *mapLayer;
public:
    virtual bool init();
    static Scene *createScene();
    CREATE_FUNC(Game01);

//    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};
#endif /* Game01_hpp */
