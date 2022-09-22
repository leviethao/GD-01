#include "Lesson1.h"

USING_NS_CC;

Scene* Lesson1::createScene()
{
    return Lesson1::create();
}


// on "init" you need to initialize your instance
bool Lesson1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* mySprite = Sprite::create("images/Star.png");
    mySprite->setPosition(100, 100);
    addChild(mySprite);

    return true;
}

