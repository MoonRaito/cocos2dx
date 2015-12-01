//
//  SpriteBase.hpp
//  cocosTest01
//
//  Created by Moon on 15/12/1.
//
//

#ifndef SpriteBase_hpp
#define SpriteBase_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

// 扩展精灵类，增加生命值、血条等属性
class SpriteBase:public cocos2d::Sprite
{
private:
    int _lifeValue; // 精灵的生命值
    LoadingBar* _HP;// 精灵血条
    float _HPInterval; // 血条的更新量
    bool _move; // 是否移动
    int _moveCount; // 移动次数
public:
    // 静态的create 函数
    static SpriteBase* create(const std::string& filename)
    {
        SpriteBase *sprite = new SpriteBase();
        if (sprite && sprite->initWithFile(filename)) {
            sprite->autorelease();
            return sprite;
        }
        CC_SAFE_DELETE(sprite);
        return nullptr;
    }
    void setLifeValue(int lifeValue){_lifeValue=lifeValue;}
    int getLifeValue(){return _lifeValue;}
    void setHP(LoadingBar* HP){_HP=HP;}
    LoadingBar* getHP(){return _HP;}
    void setHPInterval(float HPInterval){_HPInterval = HPInterval;}
    int getHPInterval(){return _HPInterval;}
    void setMove(bool move){_move = move;}
    bool getMove(){return _move;}
    void setMoveCount(int moveCount){_moveCount = moveCount;}
    int getMoveCount(){return _moveCount;}
};

#endif /* SpriteBase_hpp */
