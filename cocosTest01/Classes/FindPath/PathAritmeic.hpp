//
//  PathAritmeic.hpp
//  cocosTest01
//
//  Created by Moon on 15/12/1.
//
//

#ifndef PathAritmeic_hpp
#define PathAritmeic_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"
#include "Grid.hpp"
#include "PointDelegate.hpp"
USING_NS_CC;
// 使用命名空间
using namespace std;
// 枚举，代表地图的宽和高
enum{
    mapWidth = 30,
    mapHeight = 20
};

class PathArithmetic:public cocos2d::Ref{
private:
    // 记录已经经过的点
    Vector<PointDelegate*> _invalidPoints;
    // 记录有效路径的点
    Vector<PointDelegate*> _pathPoints;
    
    bool isHavePath(Vector<PointDelegate*> allPath,Vec2 checkPath);
public:
    // 静态的create函数
    static PathArithmetic* create(){
        PathArithmetic* p =new PathArithmetic();
        if(p){
            p->autorelease();
        }else{
            CC_SAFE_DELETE(p);
        }
        return p;
    }
    
    /**
     *  寻路函数
     *  @param from 开始点
     *  @param to 结束点
     *  @param gridVector 网格二维数组
     *  @return 开始点from到结束点to的最佳（短）路径
     */
    Vector<PointDelegate*> getPath(Vec2 from,Vec2 to,std::vector<Vector<Grid*>> gridVector);
    
    /**
     *  查找有效路径函数（递归搜索）
     *  @param from 开始点
     *  @param to 结束点
     *  @param gridVector 网格二维数组
     *  @return true 有效路径 false 无效路径
     */
    bool findValidGrid(Vec2 from,Vec2 to,std::vector<Vector<Grid*>> gridVector,float f,float g,float h);
    /**
     *  检查point点的有效性（是否可以通过）
     *  @parm point 点
     *  @parm gridVector 地图二维数组
     *  @return true 有效 false 无效
     */
    bool isCheck(Vec2 point,std::vector<Vector<Grid*>> gridVector);
    
    bool findValidGrid_1_0_1(Vec2 from, Vec2 to, vector<Vector<Grid*>> _gridArray);
    // 判断 是否 检查过
    // 检查Point点的有效性（是否可以通过）
    bool isCheck_1_0_1(Vec2 point, std::vector<Vector<Grid*>> _gridVector);
    
    // 寻路函数
    Vector<PointDelegate*> getPath_1_0_1(Point from, Point to, vector<Vector<Grid*>> _gridArray);
    
    // 寻找的过的节点
    Vector<PointDelegate*> getPath_1_0_2(Point from, Point to, vector<Vector<Grid*>> _gridArray);
    
};
#endif /* PathAritmeic_hpp */




























