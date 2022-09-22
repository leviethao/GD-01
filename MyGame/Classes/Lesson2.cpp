#include "Lesson2.h"

USING_NS_CC;

Scene* Lesson2::createScene()
{
    return Lesson2::create();
}


// on "init" you need to initialize your instance
bool Lesson2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //Sprite* mySprite1 = Sprite::create("images/Star.png");
    //mySprite1->setPosition(0, 0);
    //mySprite1->setLocalZOrder(1);
    //addChild(mySprite1);

    //Sprite* mySprite2 = Sprite::create("images/Star.png", Rect(0, 0, 100, 100));
    //mySprite2->setPosition(100, 100);
    //addChild(mySprite2);

    //Sprite* mySprite3 = Sprite::create("images/Star.png");
    //mySprite3->setPosition(visibleSize / 2);
    ////mySprite3->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    ////mySprite3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    ////mySprite3->setPosition(Vec2::ZERO);
    //addChild(mySprite3);
    //mySprite3->setAnchorPoint(Vec2(0.5, 0.5));
    //mySprite3->setRotation(390);

    //log("Rotation: %.2f", mySprite3->getRotation());
    //log("Position: %.2f, %.2f", mySprite3->getPosition().x, mySprite3->getPosition().y);

    //Sprite* mySpriteCenter = Sprite::create("images/Star.png");
    //mySpriteCenter->setPosition(visibleSize / 2);
    //mySpriteCenter->setContentSize(Size(10, 10));
    //mySpriteCenter->setLocalZOrder(2);
    //addChild(mySpriteCenter);

    //Sprite* mySpriteScale = Sprite::create("images/Star.png");
    //mySpriteScale->setPosition(visibleSize.width * 0.3, visibleSize.height * 0.7);
    //mySpriteScale->setScale(2);
    //mySpriteScale->setColor(Color3B(177, 17, 245));
    ////mySpriteScale->setColor(Color3B::BLUE);
    //mySpriteScale->setOpacity(255);
    //addChild(mySpriteScale);

    //Sprite* mySpriteSkew = Sprite::create("images/Star.png");
    //mySpriteSkew->setPosition(visibleSize.width * 0.7, visibleSize.height * 0.5);
    //mySpriteSkew->setSkewY(-30);
    //addChild(mySpriteSkew);

    //auto childNode = Sprite::create("images/Star.png");
    //childNode->setContentSize(Size(50, 50));
    //childNode->setPosition(mySpriteSkew->getContentSize() * 1.5);
    //childNode->setRotation(30);
    //mySpriteSkew->addChild(childNode);

    //log("Child node skewY = %.2f", childNode->getSkewY());

    const int ROW_NUM = 4;
    const int COL_NUM = 6;
    const float ITEM_WIDTH = visibleSize.width / COL_NUM;
    const float ITEM_HEIGH = visibleSize.height / ROW_NUM;

    for (int rowIndex = 0; rowIndex < ROW_NUM; rowIndex++) {
        for (int colIndex = 0; colIndex < COL_NUM; colIndex++) {
            auto item = Sprite::create("images/Star.png");
            item->setContentSize(Size(ITEM_WIDTH, ITEM_HEIGH));
            addChild(item);

            float x = ITEM_WIDTH * colIndex;
            float y = ITEM_HEIGH * rowIndex;
            item->setAnchorPoint(Vec2(0, 0));
            item->setPosition(x, y);
        }
    }


    return true;
}

