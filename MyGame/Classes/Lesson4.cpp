#include "Lesson4.h"

USING_NS_CC;

Scene* Lesson4::createScene()
{
    return Lesson4::create();
}


// on "init" you need to initialize your instance
bool Lesson4::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->mySprite = Sprite::create("Player.png");
    this->mySprite->setContentSize(Size(50, 50));
    this->mySprite->setPosition(200, 100);
    addChild(this->mySprite);


    // Init listeners

    // Mouse event listener
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson4::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Lesson4::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Lesson4::onMouseMove, this);
    mouseListener->onMouseScroll = CC_CALLBACK_1(Lesson4::onMouseScroll, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Lesson4::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Lesson4::onKeyReleased, this);
    /*keyboardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
        log("onKeyRelease");
    };*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->direction = Vec2::ZERO;
    this->speed = 200;


    // Custom event listener
    auto customListener = EventListenerCustom::create("custom_event1", [](EventCustom* event) {
        /*float* data = static_cast<float*>(event->getUserData());
        log("Out of screen: data %.2f", *data);*/

        char* data = static_cast<char*>(event->getUserData());
        log("Out of screen: data %s", data);
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(customListener, this);


    this->isDrag = false;

    // triger rand
    srand(time(NULL));

    /*for (int i = 0; i < 10; i++) {
        spawnEnemy();
    }*/

    schedule([&](float dt) {
        spawnEnemy();
    }, 2, "SpawnEnemy");

    scheduleUpdate();
    return true;
}

void Lesson4::update(float dt) {
    Vec2 curPos = this->mySprite->getPosition();
    this->mySprite->setPosition(curPos + speed * dt * direction);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Dispatch custom event when mySprite move to right edge
    if (this->mySprite->getPositionX() > visibleSize.width) {
        EventCustom customEvent1("custom_event1");
        /*float val = 2.5;
        customEvent1.setUserData(&val);*/
        char* val = "Out of screen!!!!";
        customEvent1.setUserData(val);
        _eventDispatcher->dispatchEvent(&customEvent1);
    }


    // Move bullet
    for (auto bullet : this->bulletList) {
        float bulletSpeed = 200;
        Vec2 currentPos = bullet->getPosition();
        float angle = bullet->getRotation() * -1;
        Vec2 direction = Vec2(0, 1);
        direction.rotate(Vec2::ZERO, angle * M_PI / 180);
        bullet->setPosition(currentPos + bulletSpeed * dt * direction);
    }

    // Handle collision
    for (int i = 0; i < this->enemyList.size(); i++) {
        for (auto bullet : this->bulletList) {
            if (enemyList[i]->getBoundingBox()
                .intersectsRect(bullet->getBoundingBox())) {
                //enemy->setColor(Color3B::BLACK);
                enemyList[i]->removeFromParentAndCleanup(true);
                this->enemyList.erase(enemyList.begin() + i);
                i--;
                break;
            }
        }
    }
}


void Lesson4::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();
    //this->mySprite->setPosition(location);

    /*this->mySprite->stopAllActions();
    this->mySprite->runAction(MoveTo::create(1, location));*/

    //log("MouseDown Location: (%.2f, %.2f)", location.x, location.y);

    // Check mouse click on mySprite
    if (this->mySprite->getBoundingBox().containsPoint(location)) {
        log("MySprite location: %.2f, %.2f", this->mySprite->getPositionX(),
            this->mySprite->getPositionY());

        this->isDrag = true;
    }


    // shooting bullet
    Sprite* bullet = Sprite::create("Bullet.png");
    bullet->setContentSize(Size(15, 20));
    Vec2 distance = this->mySprite->getContentSize().height * 0.7 * aimDirection;
    Vec2 bulletPos = this->mySprite->getPosition() + distance;
    bullet->setPosition(bulletPos);

    float radian = aimDirection.getAngle(Vec2(0, 1));
    float angle = radian * 180 / M_PI;
    bullet->setRotation(angle);

    addChild(bullet);
    this->bulletList.push_back(bullet);

    // add particle system
    auto particle = ParticleMeteor::create();
    particle->setGravity(Vec2(0, 0));
    particle->setLife(0.5);
    particle->setStartSize(30);
    particle->setEndSize(0);
    particle->setPosition(bullet->getContentSize().width / 2, -10);
    bullet->addChild(particle);


    //bullet->runAction(MoveTo::create(1, aimDirection * 1000));
}

void Lesson4::onMouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();

    //log("MouseUp Location: (%.2f, %.2f)", location.x, location.y);

    this->isDrag = false;

}

void Lesson4::onMouseMove(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();

    //this->mySprite->setPosition(location);
   /* this->mySprite->stopAllActions();
    this->mySprite->runAction(MoveTo::create(0.05, location));*/
   

    //log("MouseMove Location: (%.2f, %.2f)", location.x, location.y);
    if (this->isDrag == true) {
        this->mySprite->setPosition(location);
    }

    // player aim to mouse location
    aimDirection = location - this->mySprite->getPosition();
    aimDirection.normalize();
    float radian = aimDirection.getAngle(Vec2(0, 1));
    float angle = radian * 180 / M_PI;
    this->mySprite->setRotation(angle);
}

void Lesson4::onMouseScroll(Event* event) {
    EventMouse* e = (EventMouse*)event;

    log("MouseScroll scrollX: %.2f, scrollY: %.2f", e->getScrollX(), e->getScrollY());
}

void Lesson4::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
        direction.x = -1;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        direction.x = 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        direction.y = -1;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        direction.y = 1;
        break;
    default:
        break;
    }

    direction.normalize();
}
void Lesson4::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_D:
        direction.x = 0;
        break;
    case EventKeyboard::KeyCode::KEY_S:
    case EventKeyboard::KeyCode::KEY_W:
        direction.y = 0;
        break;
    default:
        break;
    }

    direction.normalize();
}

void Lesson4::spawnEnemy() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto enemy = Sprite::create("Enemy1.png");
    enemy->setContentSize(Size(50, 50));

    const int MIN_X = origin.x;
    const int MAX_X = origin.x + visibleSize.width;
    const int MIN_Y = origin.y;
    const int MAX_Y = origin.y + visibleSize.height;

    float xPos = rand() % int(MAX_X - MIN_X);
    float yPos = rand() % int(MAX_Y - MIN_Y);
    enemy->setPosition(xPos, yPos);
    addChild(enemy);
    this->enemyList.push_back(enemy);
}