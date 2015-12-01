#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Map01.hpp"
#include "Game01.hpp"
#include "MapTest01.hpp"
#include "FindPath/GameScene.hpp"
#include "FindPath/MyGame.hpp"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//
//    addChild(rootNode);
    
    
//    Sprite *s = Sprite::create("whah");
//    this->addChild(s);
    
//    MenuItemFont *item = MenuItemFont::create("ylyTest 按钮 01");
//    
//    Menu *m = Menu::create(item,NULL);
//    
//    this->addChild(m);
//
//    return true;
//}
    
//    Vec2 winSize = Director::getInstance()->getWinSize();
    
    // 可见视图大小
    Size visiblesSize = Director::getInstance()->getVisibleSize();
    
    MenuItemFont *item = MenuItemFont::create("开始游戏",CC_CALLBACK_1(HelloWorld::onMenuItem,this));
    
    MenuItemFont *gameMap = MenuItemFont::create("游戏地图",CC_CALLBACK_1(HelloWorld::onMenuItemGameMap,this));
    
//    gameMap->setPosition(Vec2(visiblesSize.width/2, visiblesSize.height/2-30));
    
//    gameMap->setAnchorPoint(Vec2(visiblesSize.width/2, visiblesSize.height/2-30));
    // 锚点和位置
//    gameMap->setAnchorPoint(Vec2::ZERO);
    
    gameMap->setPosition(Vec2(0.0, -50));
    
    
    MenuItemFont *myGame = MenuItemFont::create("myGame",CC_CALLBACK_1(HelloWorld::onMenuItemMyGame,this));
    myGame->setPosition(Vec2(0.0, -100));

    
    Menu *menu = Menu::create(item,gameMap,myGame,NULL);
    
    
    this->addChild(menu);
    
    return true;
}

void HelloWorld::onMenuItem(Ref *ref)
{
    //    CCLOG("OK...");
    //    Scene *scene = Map01::createScene();
    //    Scene *scene = Game01::createScene();
        Scene *scene = MapTest01::createScene();
    TransitionFade *transitionFade = TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionFade);
    // replaceScene 每次销毁前一场景
    // push 不销毁
    //    Director::getInstance()->pushScene(scene);
    
    // pop 
    
}

void HelloWorld::onMenuItemGameMap(Ref *ref)
{
    //    CCLOG("OK...");
//        Scene *scene = Map01::createScene();
    //    Scene *scene = Game01::createScene();
//    Scene *scene = MapTest01::createScene();
    Scene *scene = Game::createScene();
    TransitionFade *transitionFade = TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionFade);
    // replaceScene 每次销毁前一场景
    // push 不销毁
    //    Director::getInstance()->pushScene(scene);
    
    // pop
    
}

void HelloWorld::onMenuItemMyGame(Ref *ref)
{
    //    CCLOG("OK...");
    //        Scene *scene = Map01::createScene();
    //    Scene *scene = Game01::createScene();
    //    Scene *scene = MapTest01::createScene();
    Scene *scene = MyGame::createScene();
    TransitionFade *transitionFade = TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionFade);
    // replaceScene 每次销毁前一场景
    // push 不销毁
    //    Director::getInstance()->pushScene(scene);
    
    // pop
    
}