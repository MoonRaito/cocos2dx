//
//  PathAritmeic.cpp
//  cocosTest01
//
//  Created by Moon on 15/12/1.
//
//

#include "PathAritmeic.hpp"


// 检查Point点的有效性（是否可以通过）
bool PathArithmetic::isCheck(Vec2 point, std::vector<Vector<Grid*>> _gridVector){
    // x和y 小于0返回false
    if(point.x<0||point.y<0){
        return false;
    }
    // _invalidPoints 中记录已经经过的点，如果该集合中包含这个点，返回false
    for(int i = 0 ;i<_invalidPoints.size();i++){
        PointDelegate* pp = _invalidPoints.at(i);
        Vec2 t = Vec2(pp->getX(),pp->getY());
        if (point.equals(t)) {
            return false;
        }
    }
    // x和y超出地图宽度和高度时返回false
    if (point.x>=mapWidth||point.y>=mapHeight) {
        return false;
    }
    
    PointDelegate* g = PointDelegate::create(point.x, point.y);
    // 从二维数组中获取当前点所代表的地图网格，判断x,y代表的点是否可以通过（有障碍物则不能通过）
    Vector<Grid*> tempX = _gridVector.at((int)g->getX());
    Grid* grid = tempX.at((int)g->getY());
    if(point.x>=0&&point.y>=0&&grid->isPass()){
        return true;
    }
    return false;
}


// 查找有效路径函数（递归搜索）
bool PathArithmetic::findValidGrid(Vec2 from, Vec2 to, vector<Vector<Grid*>> _gridArray
                                   ,float f,float g,float h){
    // 因为Vector 不支持存储Point,所以使用一个代理类PointDelegate储存Point的x和y
    PointDelegate* fromDelegate = PointDelegate::create(from.x, from.y,f,g,h);
    //（1） 记录走过的点，之后的点如果存在这个集合当中，则视为无效点，不再重复记录
    _invalidPoints.pushBack(fromDelegate);
    // (2) 判断当前点的上、右、左、下、左上、右上、右下8个点是否有效或者是目的点
    // 使用临时Vector集合存储需要检测的8个点
    Vector<PointDelegate*> points;
    points.pushBack(PointDelegate::create(from.x, from.y-1));
    points.pushBack(PointDelegate::create(from.x, from.y+1));
    points.pushBack(PointDelegate::create(from.x-1, from.y));
    points.pushBack(PointDelegate::create(from.x+1, from.y));
//    points.pushBack(PointDelegate::create(from.x-1, from.y-1));
//    points.pushBack(PointDelegate::create(from.x+1, from.y+1));
//    points.pushBack(PointDelegate::create(from.x-1, from.y+1));
//    points.pushBack(PointDelegate::create(from.x+1, from.y-1));
    // 使用临时Vector集合储存8个点中有效（是否可以通过）的点
    Vector<PointDelegate*> temp;
    for (int i= 0; i<points.size(); i++) {
        PointDelegate* pd = points.at(i);
        // 判断当前点是不是最终点的to，如果是，存储到_pathPoints集合当中，返回true；
        Vec2 p = Vec2(pd->getX(), pd->getY());
        if (p.equals(to)) {
            _pathPoints.pushBack(pd);
            return true;
        }
        // 检查当前点的有效性（前、后、左、右是否可以通过），如果可以通过，添加到临时集合temp中准备排序
        if (isCheck(p, _gridArray)) {
            temp.pushBack(pd);
        }
    }
    // (3) 对临时集合中有效点按最短路径排序。
    std::sort(temp.begin(), temp.end(), [=](const Ref* obj1,const Ref* obj2){
        PointDelegate* p1 = (PointDelegate*)obj1;
        PointDelegate* p2 = (PointDelegate*)obj2;
//        double r1 = sqrt((p1->getX()-to.x)*(p1->getX()-to.x)+(p1->getY()-to.y)*(p1->getY()-to.y));
//        double r2 = sqrt((p2->getX()-to.x)*(p2->getX()-to.x)+(p2->getY()-to.y)*(p2->getY()-to.y));
//        return r1<r2?-1:0;
        
        //        如果是整形的，就是abs()
        //        如果是浮点型的，是fabs()
                double ylyH1 = (abs(to.x-p1->getX())+ abs(to.y-p1->getY()))*10;
        log("%f*****%f******%f",to.x-p1->getX(),to.y-p1->getY(),(to.x-p1->getX())+ (to.y-p1->getY()));
                double ylyH2 = (abs(to.x-p2->getX())+ abs(to.y-p2->getY()))*10;
        
//                 ylyH1 = sqrt((p1->getX()-to.x)*(p1->getX()-to.x)+(p1->getY()-to.y)*(p1->getY()-to.y));
//                 ylyH2 = sqrt((p2->getX()-to.x)*(p2->getX()-to.x)+(p2->getY()-to.y)*(p2->getY()-to.y));
//        
        
                double f1 = ylyH1 + g;
        log("%f",g);
                double f2 = ylyH2 + g;
        
        
        p1->setF(f1);
        p1->setG(g);
        p1->setH(ylyH1);
        p2->setF(f2);
        p2->setG(g);
        p2->setH(ylyH2);
        
                return f1<f2?-1:0;
    });
    
    // 自己编写寻路
    //        如果是整形的，就是abs()
    //        如果是浮点型的，是fabs()
    //        int ylyH1 = abs(to.x-p1->getX() + to.y-p1->getY())*10;
    //        int ylyH2 = abs(to.x-p2->getX() + to.y-p2->getY())*10;
    //
    //        int f1 = ylyH1 + g;
    //        int f2 = ylyH2 + g;
    //
    //        return f1<f2?-1:0;
    
    // （4）递归找出所有有效点直到搜索到终点。
    for (int i=0; i<temp.size(); i++) {
        PointDelegate* pd = temp.at(i);
        Vec2 p = Vec2(pd->getX(),pd->getY());
        // 递归调用findValidGrid函数
        bool flag = findValidGrid(p, to, _gridArray,g+10+h,g+10,h);
        if (flag) {
            //(5)把距离最近的有效点存储到_pathPoints数组
            _pathPoints.pushBack(pd);
            return true;
        }
    }
    return false;
}

// 寻路函数
Vector<PointDelegate*> PathArithmetic::getPath(Point from, Point to, vector<Vector<Grid*>> _gridArray){
    // 调用findValidGrid 函数递归完成路径查找
    findValidGrid(from, to, _gridArray ,0.0,10.0,0.0);
    // 路径计算完成，_pathPoints 集合当中存储的是最佳路径的每一个Point点
    // 因为存储时是先加入第一步网格，再加入第二步网格，所以需要反转数组
    _pathPoints.reverse();
    // 返回最佳路径Point点集合
    return _pathPoints;
}













































