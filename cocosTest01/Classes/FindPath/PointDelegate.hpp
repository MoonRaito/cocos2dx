//
//  PointDelegate.hpp
//  cocosTest01
//
//  Created by Moon on 15/12/1.
//
//

#ifndef PointDelegate_hpp
#define PointDelegate_hpp

#include <stdio.h>
#include "cocos2d.h"

// Point 的代理类，继承cocos2d::Ref类
class PointDelegate : public cocos2d::Ref{
private:
    float _x;
    float _y;
    
    /**ylyAdd start***/
    float _f;
    float _g;
    float _h;
    
    bool _opend;
    bool _closed;
    
    bool _walkable;
    
    PointDelegate* _parent;
    /**ylyAdd end***/
public:
    static PointDelegate* create(float x,float y){
        PointDelegate* p = new PointDelegate();
        if (p&&p->initPoint(x,y)) {
            p->autorelease();
            return p;
        }
        CC_SAFE_DELETE(p);
        return nullptr;
    }
    bool initPoint(float x,float y){
        _x = x;
        _y = y;
        return true;
    }
    static PointDelegate* create(float x,float y,float f,float g,float h){
        PointDelegate* p = new PointDelegate();
        if (p&&p->initPoint(x,y,f,g,h)) {
            p->autorelease();
            return p;
        }
        CC_SAFE_DELETE(p);
        return nullptr;
    }
    bool initPoint(float x,float y,float f,float g,float h){
        _x = x;
        _y = y;
        _f = f;
        _g = g;
        _h = h;
        return true;
    }
    void setX(float x){_x = x;}
    float getX(){return _x;}
    void setY(float y){_y = y;}
    float getY(){return _y;}
    
    /**ylyAdd start***/
    void setF(float f){_f = f;}
    float getF(){return _f;}
    void setG(float g){_g = g;}
    float getG(){return _g;}
    void setH(float h){_h = h;}
    float getH(){return _h;}
    
    void setOpend(bool opend){_opend = opend;}
    bool getOpend(){return _opend;}
    void setClosed(bool closed){_closed = closed;}
    bool getClosed(){return _closed;}
    
    void setWalkable(float walkable){_walkable = walkable;}
    bool getWalkable(){return _walkable;}
    
    void setParent(PointDelegate* parent){_parent = parent;}
    PointDelegate* getParent(){return _parent;}
    /**ylyAdd end***/
};

#endif /* PointDelegate_hpp */
