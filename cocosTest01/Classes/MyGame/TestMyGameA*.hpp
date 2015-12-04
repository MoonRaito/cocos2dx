//
//  TestMyGameA*.hpp
//  cocosTest01
//
//  Created by Moon on 15/12/2.
//
//

#ifndef TestMyGameA__hpp
#define TestMyGameA__hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
#include "../MyGame/SpriteBase.hpp"
#include "../MyGame/PathAritmeic.hpp"
// 使用命名空间
using namespace std;
USING_NS_CC;
// 游戏主场景
class TestMyGame : public cocos2d::Layer{
private:
    TMXTiledMap* _titleMap; // 地图
    Sprite* _player; // 玩家精灵
    Vector<SpriteBase*>* _monsterArray; // 怪物数组
    TMXLayer* _collidable; // 障碍物
    int _screenWidth,_screenHeight; // 屏幕宽度和高度
    int _count; // 游戏帧计数器
    
    vector<Vector<Grid*>> _gridVector; // 网格集合（网格二维数组）
    
    // 将屏幕的OpenGL坐标转换为TileMap坐标
    Vec2 tileCoordForPosition(Vec2 position);
    
    Vec2 bgOrigin;
    
    bool _isTouchesMoved;  // 是否 点击移动
    Sprite* _sPath; // 精灵路径
    Vector<Sprite*> _vsPath; // 精灵路径集合
public:
    /**
     * 静态函数，创建Scene场景
     * 注意：在Cocos2d-x中没有Cocos2d-iPhone中的“id”，建议返回实例的指针
     */
    static cocos2d::Scene* createScene();
    /**
     * init函数，完成初始化操作
     * 注意：在Cocos2d-x中返回bool值，而不是返回Cocos2d-iPhone中的“id”
     */
    virtual bool init();
    // 回调更新函数，该函数每一帧都会调用
    void update(float delta);
    
    
    // 玩家根据最佳路径点移动
    void playerMoveWithWayPoints(Vec2 position,Vector<PointDelegate*> path);
    // title 坐标转换为gl坐标
    Point locationForTilePos(Vec2 pos);
    
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
    /**
     * 使用CREATE_FUNC宏创建当前类的对象，返回的对象将会由自动释放池管理内存的释放
     */
    CREATE_FUNC(TestMyGame);
};

#endif /* TestMyGameA__hpp */
