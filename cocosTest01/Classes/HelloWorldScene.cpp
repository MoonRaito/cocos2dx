#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "Map01.hpp"

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
    MenuItemFont *item = MenuItemFont::create("开始游戏",CC_CALLBACK_1(HelloWorld::onMenuItem,this));
    
    Menu *menu = Menu::create(item,NULL);
    
    
    this->addChild(menu);
    
    return true;
}

void HelloWorld::onMenuItem(Ref *ref)
{
    //    CCLOG("OK...");
    Scene *scene = Map01::createScene();
    TransitionFade *transitionFade = TransitionFade::create(2, scene);
    Director::getInstance()->replaceScene(transitionFade);
    // replaceScene 每次销毁前一场景
    // push 不销毁
    //    Director::getInstance()->pushScene(scene);
    
    // pop 
    
}