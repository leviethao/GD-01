#include "Lesson9.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Lesson9::createScene()
{
    return Lesson9::create();
}


// on "init" you need to initialize your instance
bool Lesson9::init()
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



    // Menu audio features
    Vector<MenuItem*> menuItems = {
        MenuItemLabel::create(Label::createWithSystemFont("Preload", "Arial", 20),
        [=](Ref* sender) {
            AudioEngine::preload("sounds/background.mp3", [](bool isSuccess) {
                log("Preload background.pm3 %s", isSuccess ? "Success" : "Failed");
            });
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Play", "Arial", 20),
            [=](Ref* sender) {
            this->backgroundMusic = AudioEngine::play2d("sounds/background.mp3", true);
            log("backgroundMusic: %d", this->backgroundMusic);
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Pause", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::pause(this->backgroundMusic);
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Resume", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::resume(this->backgroundMusic);
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Pause All", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::pauseAll();
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Resume All", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::resumeAll();
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Stop", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::stop(this->backgroundMusic);
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Stop All", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::stopAll();
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Enable Audio", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::setEnabled(true);
            //this->soundLabel->setString("Sound: ON");
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Disable Audio", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::setEnabled(false);
            //this->soundLabel->setString("Sound: OFF");
        }),
        MenuItemLabel::create(Label::createWithSystemFont("End", "Arial", 20),
            [=](Ref* sender) {
            AudioEngine::end();
            //this->soundLabel->setString("Sound: END");
        }),
    };

    auto menu = Menu::createWithArray(menuItems);
    addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));



    // Slider change audio volume
    auto slider = ui::Slider::create("ui/loadingBarBG.png", "ui/unchecked.png");
    slider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
    addChild(slider);
    slider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
        auto slider = dynamic_cast<ui::Slider*>(sender);
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            float volume = slider->getPercent() / 100.0;
            AudioEngine::setVolume(this->backgroundMusic, volume); //0 - 1
        }
        });


    return true;
}

