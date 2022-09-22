#include "ClosingScene.h"

USING_NS_CC;

int score = 0;

Scene* ClosingScene::createScene(int _score)
{
    score = _score;
    return ClosingScene::create();
}


// on "init" you need to initialize your instance
bool ClosingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithSystemFont("Game Over", "Arial", 30);
    label->setPosition(visibleSize / 2);
    addChild(label);

    const std::string strScore = "Score: " + std::to_string(score);
    auto lbScore = Label::createWithSystemFont(strScore, "Arial", 24);
    lbScore->setPosition(Vec2(visibleSize.width / 2,
        visibleSize.height * 0.4));
    addChild(lbScore);

    return true;
}

