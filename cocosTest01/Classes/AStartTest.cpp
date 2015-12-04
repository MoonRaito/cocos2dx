//
//  AStartTest.cpp
//  cocosTest01
//
//  Created by Moon on 15/12/3.
//
//

#include "AStartTest.hpp"

Scene *AStartTest::createScene()
{
    Scene *scene = Scene::create();
    AStartTest *layer = AStartTest::create();
    scene->addChild(layer);
    return scene;
}


bool AStartTest::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    /***添加砖块地图***/
    TMXTiledMap *map = TMXTiledMap::create("map04_1.tmx");
    map->setAnchorPoint(Vec2::ZERO);
    map->setPosition(Vec2::ZERO),
    bgSprite->addChild(map, 1);
    
    
    /*******添加人物角色 start**********/
    // 调用TMXTiledMap 的 getObjectGroup 方法获取对象层
    auto objects = map->getObjectGroup("object01");
    // 根据对象名称获取对象信息
    ValueMap tmap = objects->getObject("player01");
    // 获取地图中设置的player对象的X和Y值
    int x = tmap.at("x").asInt();
    int y = tmap.at("y").asInt();
    Sprite *player01 = Sprite::create("player01.png");
    player01->setPosition(x,y);
    // 将玩家精灵添加为地图的子节点
    this->addChild(player01);
    /*******添加人物角色 end**********/
    
    
    
    
    return true;
}










// AStart 算法
bool AStartTest::findValidGrid(Vec2 from, Vec2 to, vector<Vector<Grid*>> _gridArray){
    // 因为Vector 不支持存储Point,所以使用一个代理类PointDelegate储存Point的x和y
    PointDelegate* fromDelegate = PointDelegate::create(from.x, from.y);
    //（1） 记录走过的点，之后的点如果存在这个集合当中，则视为无效点，不再重复记录
    _invalidPoints.pushBack(fromDelegate);
    fromDelegate->setOpend(true);
    
    int x = 0, y = 0;
    int ng = 0;
    while (!_invalidPoints.empty()) {
        _node = _invalidPoints.back();
        _node->setClosed(true);
        
        Vec2 node = Vec2(_node->getX(), _node->getY());
        if(node.equals(to) ){
            // 回溯方法 返回 查找的 路径  暂未 编写
            return true;
        }
        
        Vector<PointDelegate*> neighbors = this->getNeighbors(node, _gridArray);
        PointDelegate* neighbor;
        for (int i = 0; i<neighbors.size(); i++) {
            neighbor = neighbors.at(i);
            if (neighbor->getClosed()) {  // 节点已经走过
                continue;
            }
            x = neighbor->getX();
            y = neighbor->getY();
            
            // 计算相对于当前节点，此邻节点的g(n)
            ng = _node->getG() + ((x - node.x == 0 || y - node.y == 0) ? 10 : 14);
            
            // 如果此邻节点没检查过，或者检查过了但新g(n)更好
            if(!_node->getOpend()||ng<neighbor->getG()){
                neighbor->setG(ng);
                neighbor->setH(neighbor->getH() || mapWidth * (abs(x - to.x) + abs(y - to.y) *10));
                neighbor->setF(neighbor->getG()+neighbor->getH());
                neighbor->setParent(_node);
                
                if (!neighbor->getOpend()) {
                    _invalidPoints.pushBack(neighbor);
                    neighbor->setOpend(true);
                }else{
                    
                }
            }
            
        }
        
        
        
        
        
    }
    
    
    
    
    return true;
}


// 检查Point点的有效性（是否可以通过）
bool AStartTest::isCheck(Vec2 point, std::vector<Vector<Grid*>> _gridVector){
    return this->isInside(point)&&this->isWalkableAt(point, _gridVector);
}

// 是否可以走
bool AStartTest::isWalkableAt(Vec2 point, std::vector<Vector<Grid*>> _gridVector) {
    PointDelegate* g = PointDelegate::create(point.x, point.y);
    // 从二维数组中获取当前点所代表的地图网格，判断x,y代表的点是否可以通过（有障碍物则不能通过）
    Vector<Grid*> tempX = _gridVector.at((int)g->getX());
    Grid* grid = tempX.at((int)g->getY());
    if(point.x>=0&&point.y>=0&&grid->isPass()){
        return true;
    }
    return false;
}

bool AStartTest::isInside(Vec2 point) {
    // x和y 小于0返回false
    if(point.x<0||point.y<0){
        return false;
    }
    // x和y超出地图宽度和高度时返回false
    if (point.x>=mapWidth||point.y>=mapHeight) {
        return false;
    }
    return true;
}

// 周围可以走的
Vector<PointDelegate*>  AStartTest::getNeighbors(Vec2 from, std::vector<Vector<Grid*>> _gridVector) {
    Vector<PointDelegate*> points;
    points.pushBack(PointDelegate::create(from.x, from.y-1));
    points.pushBack(PointDelegate::create(from.x, from.y+1));
    points.pushBack(PointDelegate::create(from.x-1, from.y));
    points.pushBack(PointDelegate::create(from.x+1, from.y));
    // 使用临时Vector集合储存8个点中有效（是否可以通过）的点
    Vector<PointDelegate*> temp;
    for (int i= 0; i<points.size(); i++) {
        PointDelegate* pd = points.at(i);
        // 判断当前点是不是最终点的to，如果是，存储到_pathPoints集合当中，返回true；
        Vec2 p = Vec2(pd->getX(), pd->getY());
        // 检查当前点的有效性（前、后、左、右是否可以通过），如果可以通过，添加到临时集合temp中准备排序
        if (this->isCheck(p, _gridVector)) {
            temp.pushBack(pd);
        }
    }
    return temp;
};





























