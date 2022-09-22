#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}


// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // Loading bar background
    auto loadingBarBG = Sprite::create("ui/loadingBarBG.png");
    loadingBarBG->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height * 0.5));
    //loadingBarBG->setContentSize(Size(200, 40));
    loadingBarBG->setAnchorPoint(Vec2(0, 0.5));
    addChild(loadingBarBG);

    // Loading bar
    loadingBar = ui::LoadingBar::create("ui/loadingBar.png");
    loadingBar->setAnchorPoint(Vec2(0, 0.5));
    //loadingBar->setContentSize(Size(200, 40));

    loadingBar->setPosition(loadingBarBG->getPosition());
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(0);
    addChild(loadingBar);


    /*schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent++;
        loadingBar->setPercent(percent);

        if (percent >= 100) {
            loadingBar->setPercent(100);
            unschedule("updateLoadingBar");
            auto gameScene = GameScene::createScene();
            Director::getInstance()->replaceScene(
                TransitionFade::create(0.5, gameScene)
            );
        }
        }, 0.05, "updateLoadingBar");*/

    log("start loading img30mb.jpg");
    Director::getInstance()->getTextureCache()
        ->addImageAsync("img30mb.jpg", [&](Texture2D* texture) {
            loadingBar->setPercent(50);
            log("start loading img30mb2.jpg");
            Director::getInstance()->getTextureCache()
                ->addImageAsync("img30mb2.jpg",
                    CC_CALLBACK_1(LoadingScene::allTexturesLoaded, this));
        });

    return true;
}

void LoadingScene::allTexturesLoaded(Texture2D* texture) {
    loadingBar->setPercent(100);
    log("all images loaded");

    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(
        TransitionFade::create(0.5, gameScene)
    );
}