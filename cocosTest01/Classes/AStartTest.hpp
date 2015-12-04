//
//  AStartTest.hpp
//  cocosTest01
//
//  Created by Moon on 15/12/3.
//
//

#ifndef AStartTest_hpp
#define AStartTest_hpp

#include <stdio.h>
#include "cocos2d.h"

#include <vector>
#include "Grid.hpp"
#include "PointDelegate.hpp"
// 使用命名空间
using namespace std;
using namespace cocos2d;

// 枚举，代表地图的宽和高
enum{
    mapWidth = 32,
    mapHeight = 32
};

class AStartTest:public Layer{
private:
    Sprite* bgSprite;
    Vec2 bgOrigin;
    
    // 记录已经经过的点 open
    Vector<PointDelegate*> _invalidPoints;
    // 记录有效路径的点 close
    Vector<PointDelegate*> _pathPoints;
    
    PointDelegate* _node;
public:
    virtual bool init();
    static Scene *createScene();
    
    
    /**
     *  查找有效路径函数
     *  @param from 开始点
     *  @param to 结束点
     *  @param gridVector 网格二维数组
     *  @return true 有效路径 false 无效路径
     */
    bool findValidGrid(Vec2 from,Vec2 to,std::vector<Vector<Grid*>> gridVector);
    
    /**
     * 是否超出边界
     */
    bool isInside(Vec2 point);
    /**
     * 是否可以走
     */
    bool isWalkableAt(Vec2 point, std::vector<Vector<Grid*>> _gridVector);
    /**
     * 是否有效点
     */
    bool isCheck(Vec2 point, std::vector<Vector<Grid*>> _gridVector);
    
    /**
     * 周围的临时点
     */
    Vector<PointDelegate*> getNeighbors(Vec2 from, std::vector<Vector<Grid*>> _gridVector);
    
    CREATE_FUNC(AStartTest);
    
};
#endif /* AStartTest_hpp */
