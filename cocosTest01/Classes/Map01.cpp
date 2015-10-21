//
//  Map01.cpp
//  cocosTest01
//
//  Created by Moon on 15/10/21.
//
//

#include "Map01.hpp"
Scene *Map01::createScene()
{
    Scene *scene = Scene::create();
    Map01 *layer = Map01::create();
    scene->addChild(layer);
    return scene;
}

bool Map01::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    
    TMXTiledMap *map = TMXTiledMap::create("hywzmap01.tmx");
    
    this->addChild(map);
    
    return true;
}
