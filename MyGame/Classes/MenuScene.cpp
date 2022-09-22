#include "MenuScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}


// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto layerBackground = LayerColor::create(Color4B::GRAY);
    addChild(layerBackground);


    auto label = Label::createWithSystemFont("Menu Scene",
        "Arial", 50);
    label->setPosition(visibleSize / 2);
    addChild(label);

    /*auto sprite = Sprite::create("scrollviewItem.jpg");
    addChild(sprite);*/

    scheduleOnce([](float dt) {
        Director::getInstance()->popScene();
    }, 4, "closeMenu");

    return true;
}

