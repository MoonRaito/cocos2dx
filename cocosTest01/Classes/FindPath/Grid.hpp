//
//  Grid.hpp
//  cocosTest01
//
//  Created by Moon on 15/11/30.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include <stdio.h>
#include "cocos2d.h"
// 网格类，继承 cocos2d::Ref类
class Grid : public cocos2d::Ref{
private:
    int _x;         // 在地图二维数组中的x坐标
    int _y;         // 在地图二维数组中的y坐标
    bool _pass;     // 是否可以通过的变量（有障碍物则不能通过）
public:
    // 静态的create函数
    static Grid *create(int x,int y){
        Grid *g = new Grid();
        if(g && g->initWithPoint(x,y))
        {
            g->autorelease();
            return g;
        }
        CC_SAFE_DELETE(g);
        return nullptr;
    }
    bool initWithPoint(int x,int y){
        _x = x;
        _y = y;
        _pass = true;
        return true;
    }
    void setX(int x){_x=x;}
    int getX(){return _x;}
    void setY(int y){_y=y;}
    int getY(){return _y;}
    void setPass(bool pass){_pass = pass;}
    bool isPass(){return _pass;}
};
#endif /* Grid_hpp */
