//
//  MapTest01.hpp
//  cocosTest01
//
//  Created by Moon on 15/11/30.
//
//

#ifndef MapTest01_hpp
#define MapTest01_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class MapTest01:public Layer{
private:
    Vec2 bgOrigin;
    Layer *mapLayer;
    TMXTiledMap *map;
    Sprite *player01;
public:
    virtual bool init();
    static Scene *createScene();
    CREATE_FUNC(MapTest01);
    
    //    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
};
#endif /* MapTest01_hpp */
