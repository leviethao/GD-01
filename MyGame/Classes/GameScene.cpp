#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "ClosingScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithSystemFont("Game Scene",
        "Arial", 30);
    label->setPosition(visibleSize / 2);
    addChild(label);


    // Button without image
    auto button2 = ui::Button::create();
    button2->setTitleText("Menu");
    button2->setTitleColor(Color3B::RED);
    button2->setTitleFontSize(30);
    button2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
    addChild(button2);

    //auto button = ui::Button::create("ui/btnPlay.png", "ui/btnPlaySelected.png",
    //    "ui/btnPlayDisable.png");
    //button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
    //addChild(button);

    button2->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN:
                log("button pressed value = %d");
                //Scene* menuScene = MenuScene::createScene();
                
                this->menuScene = MenuScene::createScene();
                Director::getInstance()->pushScene(
                    TransitionMoveInT::create(1, menuScene));
                break;
            case ui::Widget::TouchEventType::ENDED:
                log("button released");
                break;
            default:
                break;
        }
    });

    scheduleOnce([](float dt) {
        auto closingScene = ClosingScene::createScene(99);
        Director::getInstance()->pushScene(
            TransitionFlipX::create(0.5, closingScene)
        );
    }, 4, "openClosingScene");


    auto largeImg = Sprite::create("img30mb.jpg");
    addChild(largeImg);

    return true;
}

