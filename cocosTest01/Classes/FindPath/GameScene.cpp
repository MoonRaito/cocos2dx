//
//  GameScene.cpp
//  cocosTest01
//
//  Created by Moon on 15/12/1.
//
//

#include "GameScene.hpp"
Scene *Game::createScene()
{
    Scene *scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init(){
    // 调用父类的init方法
    if (!Layer::init()) {
        return false;
    }
    // 获取设备可见试图大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // 获取屏幕的宽度和高度
    _screenWidth = visibleSize.width;
    _screenHeight = visibleSize.height;
    // 1 调用TMXTiledMap的函数读取TileMap.tmx 文件创建一个瓦片地图对象
    _titleMap = TMXTiledMap::create("map04_1.tmx");
    // 把地图的锚点和位置都设置为原点，这样可以使地图的左下角与屏幕的左下角对齐
    _titleMap->setAnchorPoint(Vec2::ZERO);
    _titleMap->setPosition(Vec2::ZERO);
    // 将地图添加为当前层的子节点
    this->addChild(_titleMap);
    // 2 获取障碍层，并设置障碍层不可见
    _collidable = _titleMap->getLayer("collidable");
    _collidable->setVisible(false);
    /*****3 初始化读取地图所以网格，并确定网格对象是否是障碍物，将信息保存到网格二维数组****************/
    for (int i=0; i<_titleMap->getMapSize().width; i++) {
        // 内部网格集合，储存网格
        Vector<Grid*> inner;
        for (int j = 0; j<_titleMap->getMapSize().height; j++) {
            // 设置网格对象的x轴和y轴以及是否可以通过变量值将网格加入到集合
            Grid *o = Grid::create(i, j);
            inner.pushBack(o);
        }
        // 将内部几个加入到网格集合
        _gridVector.push_back(inner);
    }
    // 循环保存根据每个网格的x轴和y轴查找的对应地图的GID，判断是否可通过
    for (int i = 0; i<_gridVector.size(); i++) {
        Vector<Grid*> inner = _gridVector.at(i);
        // 循环遍历内部网格集合
        for (int j = 0; j<inner.size(); j++) {
            // 获取每一个网格对象
            Grid *grid = inner.at(j);
            // 获取每一个网格对象对应的坐标
            Vec2 tileCoord = Vec2(grid->getX(),grid->getY());
            // 使用TMXLayer类的tileGIDAt函数获取TileMap坐标系里的“全局唯一标识”GID
            int tileGid = _collidable->getTileGIDAt(tileCoord);
            if (tileGid) {
                //使用GID来查找指定tile的属性，返回一个Value
                Value properties = _titleMap->getPropertiesForGID(tileGid);
                //返回的Value实际上是一个ValueMap
                ValueMap map = properties.asValueMap();
                // 查找ValueMap，判断是否有“可碰撞”物体，
                // 如果有，设置网格对象的isPass变量为false;
                std:string value=map.at("collidable").asString();
                if (value.compare("true")==0) {
                    grid->setPass(false);
                }
            }
        }
    }
    /********* 二维数组设置结束 *******************/
    // 4 创建玩家精灵
    _player = Sprite::create("player01.png");
    // 玩家x轴镜像反转
//    _player->setFlippedX(true);
    // 设置玩家精灵屏幕位置并添加为地图的子节点
//    _player->setPosition(100,_screenHeight/2+240);
    /**
     遮挡效果的实现：zOrder
     */
//    _titleMap->addChild(_player,2);
    
    /*******yly 添加人物角色 start**********/
    // 调用TMXTiledMap 的 getObjectGroup 方法获取对象层
    auto objects = _titleMap->getObjectGroup("object01");
    // 根据对象名称获取对象信息
    ValueMap tmap = objects->getObject("player01");
    // 获取地图中设置的player对象的X和Y值
    int x = tmap.at("x").asInt();
    int y = tmap.at("y").asInt();
    _player = Sprite::create("player01.png");
    _player->setAnchorPoint(Vec2(0, 1));
    _player->setPosition(x,y);
    _titleMap->addChild(_player,99);
    /*******yly 添加人物角色 eng**********/
    
    // 5 创建事件监听器
    auto planeListener = EventListenerTouchOneByOne::create();
    // 响应触摸事件函数
    planeListener->onTouchBegan=[](Touch* touch,Event* event){return true;};
    planeListener->onTouchEnded=[=](Touch* touch,Event* event){
        //OpenGL 坐标
        Vec2 touchLocation = touch->getLocation();
        // 将触摸点坐标转换成相对的Node坐标
        Vec2 nodeLocation = this->convertToNodeSpace(touchLocation);
        // 玩家镜像反转
        if (_player->getPosition().x>nodeLocation.x) {
            if (_player->isFlippedX()==true) {
                _player->setFlippedX(false);
            }
        }else{
            if (_player->isFlippedX()==false) {
                _player->setFlippedX(true);
            }
        }
        // 用玩家位置作为起点，触摸点作为终点，在地图上查找最佳到达路径
        Point from = tileCoordForPosition(_player->getPosition());
        Point to = tileCoordForPosition(nodeLocation);
        // 如果终点是不可通过（即由障碍物）的位置，则直接return
        int tileGid = _collidable->getTileGIDAt(to);
        if (tileGid) {
            // 使用GID来查找置顶的tile的属性，返回一个value
            Value properties = _titleMap ->getPropertiesForGID(tileGid);
            // 返回的Value 实际上是一个ValueMap
            ValueMap map = properties.asValueMap();
            // 查找ValueMap，判断是否有“可碰撞的”物体，如果有，直接返回
            std::string value = map.at("collidable").asString();
            if(value.compare("true")==0){
                return;
            }
        }
        // 调用PathArithmetic对象的getPath函数获得起点到终点的最佳路径点的集合
        PathArithmetic* pa = PathArithmetic::create();
        Vector<PointDelegate*> pathVector = pa->getPath(from, to, _gridVector);
        // 在玩家精灵移动过程中，如果用户在此触摸屏幕移动玩家，而精灵没有运行动作，则直接执行移动动作
        if (_player->getNumberOfRunningActions()==0&&this->getNumberOfRunningActions()==0) {
            // 玩家根据最佳路径移动
            playerMoveWithWayPoints(nodeLocation,pathVector);
            // 地图随玩家一起移动
//            setViewPointCenter(nodeLocation);
        }else{
            // 如果精灵正在运行动作，先停止精灵动作和层动作，再执行移动动作
            _player->stopAllActions();
            this->stopAllActions();
            playerMoveWithWayPoints(nodeLocation,pathVector);
            //            setViewPointCenter(nodeLocation);
        }
        
    };
    // 添加场景优先事件监听器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(planeListener, this);
    // 游戏主循环，每帧都调用的函数
    this->scheduleUpdate();
    return true;
    
}

// tmap 转换 坐标
Vec2 Game::tileCoordForPosition(Vec2 position){
    // CC_COUNTENT_SCALE_FACTOR Retina返回2，否则返回1
    // 玩家位置的x坐标除以地图的宽，得到的是地图横向的第几个格子（tile）
    // 地图宽计算：26【格子】*64【图块的宽】 = 1680【地图宽】
    // 假如精灵在的x坐标是640，则精灵所在地图的格子计算：640【精灵位置】/64【图块宽度】 = 10 【格子】
    int x = (int)(position.x/(_titleMap->getTileSize().width/CC_CONTENT_SCALE_FACTOR()));
    
    // 玩家位置的y坐标除以地图的高，得到的是地图纵向第几个格子（tile），
    // 但是因为cocos2d-x 的y 轴（左下角）和TileMap的y轴（左上角）相反，所以使用地图的高度减去玩家位置的y坐标
    float pointHeight = _titleMap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
    int y = (int)((_titleMap->getMapSize().height*pointHeight-position.y)/pointHeight);
    return Vec2(x,y);
}


// 玩家根据最佳路径点移动函数
void Game::playerMoveWithWayPoints(Vec2 position, Vector<PointDelegate *> path){
    // 调用 getAnimateByName函数获得玩家精灵移动动画
//    auto animate = getAnimateByName("player_move_",0.4f,4);
    // 创建一个动作，重复执行Animate动画
//    auto repeatanimate = RepeatForever::create(animate);
    // 玩家精灵重复执行动画动作
//    _player->runAction(repeatanimate);
    // 定义动作集合，用来保存多个moveTo动作
    Vector<FiniteTimeAction*> actionVector;
    // 循环最佳路径点集合，创建多个MvoeTo动作，玩家将执行多个MoveTo动作完成移动
    for (int i = 0; i<path.size(); i++) {
        // 获得要移动的没一点
        PointDelegate* pd = path.at(i);
        Vec2 p = Vec2(pd->getX(),pd->getY());
        // 将tileMap的 网格转成gl坐标，即玩家需要移动的位置
        Point glPoint = locationForTilePos(p);
        // 创建一个Moveto动作，让精灵对象移动到指定位置
        MoveTo* moveTo = MoveTo::create(0.4f, glPoint);
        // 将该动作添加到临时数组
        actionVector.pushBack(moveTo);
    }
    // 创建回调动作，当MoveTo动作完成后精灵恢复最初站立状态
    auto callfunc = CallFunc::create([=]{
        // 停止动画
//        _player->stopAction(repeatanimate);
//        _player->setTexture("HelloWorld.png");
    });
    // 将回调动作加入到动作集合
    actionVector.pushBack(callfunc);
    // 按顺序执行动作集合中的动作
    auto sequence = Sequence::create(actionVector);
    
    // 执行一系列的动作
    _player->runAction(sequence);
}

// 将TileMap 坐标转换为OpenGL坐标
Vec2 Game::locationForTilePos(Vec2 pos){
    int x = (int)(pos.x*(_titleMap->getTileSize().width/CC_CONTENT_SCALE_FACTOR()));
    float pointHeight = _titleMap->getTileSize().height/CC_CONTENT_SCALE_FACTOR();
    int y = (int)((_titleMap->getMapSize().height*pointHeight)-(pos.y*pointHeight));
    return Vec2(x, y);
}


void Game::update(float delta){
    
}























