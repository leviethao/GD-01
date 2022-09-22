#include "Lesson7.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Lesson7::createScene()
{
    return Lesson7::create();
}


// on "init" you need to initialize your instance
bool Lesson7::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    initUI();
    return true;
}

void Lesson7::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background color
    LayerColor* background = LayerColor::create(Color4B::GRAY);
    addChild(background);

    // Label with system font
    auto label = Label::createWithSystemFont("Hello World", "Impact", 40);
    label->setPosition(visibleSize / 2);
    label->setTextColor(Color4B(158, 247, 247, 255));
    label->enableShadow(Color4B::YELLOW, Size(8, -8));
    //label->enableOutline(Color4B::RED, 5);
    addChild(label);

    // Label with ttf font
    auto label2 = Label::createWithTTF("Label with TTF font",
        "fonts/Bullpen3D.ttf", 30);
    label2->setPosition(visibleSize.width / 2, visibleSize.height * 0.7);
    addChild(label2);

    // Config ttf
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Bullpen3D.ttf";
    labelConfig.fontSize = 30;
    labelConfig.underline = true;

    auto label3 = Label::createWithTTF(labelConfig, "Label TTF with config");
    label3->setPosition(visibleSize.width / 2, visibleSize.height * 0.6);
    addChild(label3);

    // Button
    auto button = ui::Button::create("ui/btnPlay.png", "ui/btnPlaySelected.png",
        "ui/btnPlayDisable.png");
    button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4));
    addChild(button);

    button->setBright(false); // to disabled button


    // Button without image
    auto button2 = ui::Button::create();
    button2->setTitleText("Title");
    button2->setTitleColor(Color3B::RED);
    button2->setTitleFontSize(30);
    button2->setPosition(Vec2(visibleSize.width/ 2, visibleSize.height * 0.3));
    addChild(button2);
    int value = 10;
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            value = 5;
            log("button pressed value = %d", value);
            break;
        case ui::Widget::TouchEventType::ENDED:
            log("button released");
            break;
        default:
            break;
        }
    });


    // Create text field
    auto textfield = ui::TextField::create("Enter your name", "Arial", 30);
    textfield->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
    addChild(textfield);
    textfield->setTextColor(Color4B::RED);
    textfield->setPlaceHolderColor(Color4B(0, 255, 0, 100));
    textfield->setPasswordEnabled(true);

    //textfield->setMaxLength(10);
    textfield->setCursorEnabled(true);

    textfield->addEventListener([](Ref* sender, ui::TextField::EventType type) {
        auto _textfield = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME:
            log("Focus");
            break;
        case ui::TextField::EventType::DETACH_WITH_IME:
            log("Blur");
            break;
        case ui::TextField::EventType::INSERT_TEXT:
            log("Insert text: %s", _textfield->getString().c_str());
            break;
        case ui::TextField::EventType::DELETE_BACKWARD:
            log("Delete backward");
            break;
        default:
            break;
        }
    });


    // Checkbox
    auto checkbox = ui::CheckBox::create("ui/unchecked.png", "ui/checked.png");
    checkbox->setPosition(Vec2(visibleSize.width /2, visibleSize.height * 0.1));
    addChild(checkbox);

    checkbox->addEventListener([&](Ref* sender, ui::CheckBox::EventType type) {
        switch (type) {
        case ui::CheckBox::EventType::SELECTED:
            log("selected");
            break;
        case ui::CheckBox::EventType::UNSELECTED:
            log("Unselected");
            break;
        default:
            break;
        }
    });

    
    // Create Menu
    Vector<MenuItem*> menuItems = {
        MenuItemLabel::create(Label::createWithSystemFont("Settings", "Arial", 30),
        [&](Ref* sender) {
                log("Settings");
        }),
        MenuItemLabel::create(Label::createWithSystemFont("Quit", "Arial", 30),
        [&](Ref* sender) {
                log("Quit");
                Director::getInstance()->end();
        }),
        MenuItemImage::create("ui/btnPlay.png", "ui/btnPlaySelected.png", [&](Ref* sender) {
            log("Play");
        })
    };

    auto menu = Menu::createWithArray(menuItems);
    addChild(menu);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(visibleSize.width * 0.8, visibleSize.height * 0.7));

    // Loading bar background
    auto loadingBarBG = Sprite::create("ui/loadingBarBG.png");
    loadingBarBG->setPosition(Vec2(visibleSize.width * 0.2, visibleSize.height * 0.9));
    //loadingBarBG->setContentSize(Size(200, 40));
    loadingBarBG->setAnchorPoint(Vec2(0, 0.5));
    addChild(loadingBarBG);

    // Loading bar
    auto loadingBar = ui::LoadingBar::create("ui/loadingBar.png");
    loadingBar->setAnchorPoint(Vec2(0, 0.5));
    //loadingBar->setContentSize(Size(200, 40));
    
    loadingBar->setPosition(loadingBarBG->getPosition());
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(0);
    addChild(loadingBar);


    schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent++;
        loadingBar->setPercent(percent);

        if (percent >= 100) {
            loadingBar->setPercent(100);
            unschedule("updateLoadingBar");
        }
    }, 0.1, "updateLoadingBar");

    // Slider

    auto slider = ui::Slider::create("ui/loadingBarBG.png", "ui/unchecked.png");
    slider->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.7));
    slider->setAnchorPoint(Vec2(0, 0.5));
    addChild(slider);

    //slider->setVisible(false); // to hide a Node

    slider->addEventListener([](Ref* sender, ui::Slider::EventType type) {
        auto _slider = dynamic_cast<ui::Slider*>(sender);
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            log("slider percent: %d", _slider->getPercent());
        }
    });


    // Scroll View
    auto scrollView = ui::ScrollView::create();
    scrollView->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->setDirection(ui::ScrollView::Direction::BOTH);
    //scrollView->setBounceEnabled(true);
    scrollView->setColor(Color3B::RED);
    addChild(scrollView);

    auto sprite = Sprite::create("scrollviewItem.jpg");
    sprite->setContentSize(Size(1000, 1000));
    sprite->setPosition(sprite->getContentSize() / 2);
    scrollView->addChild(sprite);
    scrollView->setInnerContainerSize(Size(500, 2000));
    scrollView->setContentSize(Size(500, 500));
    scrollView->setBackGroundColor(Color3B::RED);


    // Create items list
    const int TOTAL_ITEMS = 11;
    const int INNER_CONTAINER_WIDTH = 500;
    const int ITEMS_OF_ROW = 3;

    const int ITEM_WIDTH = (int)(INNER_CONTAINER_WIDTH / ITEMS_OF_ROW);
    const int ITEM_HEIGHT = ITEM_WIDTH;

    std::vector<Sprite*> items;
    for (int i = 0; i < TOTAL_ITEMS; i++) {
        auto item = Sprite::create("ui/loadingBarBG.png");
        items.push_back(item);
        item->setContentSize(Size(ITEM_WIDTH / 2, ITEM_HEIGHT));
        item->setColor(Color3B::RED);
        /*item->setAnchorPoint(Vec2(0, 0));*/

        auto child = Sprite::create("ui/loadingBarBG.png");
        child->setContentSize(item->getContentSize() * 0.8);
        child->setColor(Color3B::YELLOW);
        child->setPosition(item->getContentSize() / 2);
        item->addChild(child);
    }
    /*1: 0 * ITEM_WIDTH
    2: 1 * ITEM_WIDTH
    3: 2 * ITEM_WIDTH*/
    /*0: 0
    1: 1
    2: 2
    3: 0
    4: 1
    5: 2*/

    for (int i = 0; i < items.size(); i++) {
        const int x = (i % ITEMS_OF_ROW) * ITEM_WIDTH + (ITEM_WIDTH / 2);
        const int y = (int)(i / ITEMS_OF_ROW) * ITEM_HEIGHT * -1 - (ITEM_HEIGHT / 2);
        items[i]->setPosition(Vec2(x,
            y + scrollView->getInnerContainerSize().height - ITEM_HEIGHT));
        scrollView->addChild(items[i]);

    }
}