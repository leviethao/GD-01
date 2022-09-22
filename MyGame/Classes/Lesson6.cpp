#include "Lesson6.h"

USING_NS_CC;

Scene* Lesson6::createScene()
{
    return Lesson6::create();
}


// on "init" you need to initialize your instance
bool Lesson6::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
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
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson6::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(Lesson6::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(Lesson6::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    // Keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Lesson6::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Lesson6::onKeyReleased, this);
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

    // triger rand
    srand(time(NULL));


    // Contact listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Lesson6::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(Lesson6::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


    // Collision filtering
    const int PLAYER_CATEGORY = 1; // 0001
    const int ENEMY1_CATEGORY = 2; // 0010
    const int ENEMY2_CATETORY = 4;// 0100

    /*player & enemy2
    0001 & 0010 && */
    // Player can collid with enemy1 & enemy2
    const int PLAYER_COLLISION = ENEMY1_CATEGORY + ENEMY2_CATETORY; // 0010
    // Enemy1 can collid with Player
    const int ENEMY1_COLLISION = PLAYER_CATEGORY;

    // Enemy2 can collid with Player
    const int ENEMY2_COLLISION = PLAYER_CATEGORY; 



    auto enemy1 = Sprite::create("Enemy1.png");
    enemy1->setContentSize(Size(50, 50));
    enemy1->setPosition(200, 300);
    addChild(enemy1);
    auto enemy1Body = PhysicsBody::createBox(enemy1->getContentSize(),
        PhysicsMaterial(0.1f, 0.5f, 0.5f));
    enemy1Body->setDynamic(false);
    enemy1->addComponent(enemy1Body);
    enemy1Body->setContactTestBitmask(0xFFFFFFFF);
    enemy1Body->setCategoryBitmask(ENEMY1_CATEGORY);
    enemy1Body->setCollisionBitmask(ENEMY1_COLLISION);

    auto enemy2 = Sprite::create("Enemy1.png");
    enemy2->setContentSize(Size(100, 100));
    enemy2->setPosition(400, 400);
    addChild(enemy2);
    auto enemy2Body = PhysicsBody::createBox(enemy2->getContentSize(),
        PhysicsMaterial(0.1f, 0.5f, 0.5f));
    enemy2Body->setDynamic(true);
    enemy2Body->setGravityEnable(false);
    enemy2Body->setMass(50000);
    enemy2->addComponent(enemy2Body);
    enemy2Body->setContactTestBitmask(0xFFFFFFFF);
    enemy2Body->setCategoryBitmask(ENEMY2_CATETORY);
    enemy2Body->setCollisionBitmask(ENEMY2_COLLISION);

    // add physics body to mySprite
    /*auto myBody = PhysicsBody::createCircle(mySprite->getContentSize().width / 2,
        PhysicsMaterial(0.1f, 1, 0));*/
    Vec2 points[5] = {Vec2(-30, 30), Vec2(-30, -30), Vec2(0.5, 60),
        Vec2(30, 40), Vec2(30, -50)};
    auto myBody = PhysicsBody::createPolygon(points, 5,
        PhysicsMaterial(0.1f, 0.5, 0.5));
    myBody->setDynamic(true);
    this->mySprite->addComponent(myBody);
    myBody->setContactTestBitmask(0xFFFFFFFF);
    myBody->setCategoryBitmask(PLAYER_CATEGORY);
    myBody->setCollisionBitmask(PLAYER_COLLISION);

    myBody->setGravityEnable(false);
    myBody->setMass(1000);
    //myBody->setVelocity(Vec2(500, 50));
    myBody->setLinearDamping(0.5);
    //myBody->setVelocityLimit(50);
    
    /*myBody->setAngularVelocity(-100);
    myBody->setAngularDamping(0.5);
    myBody->setAngularVelocityLimit(-10);*/

    auto boundingBox = PhysicsBody::createEdgeBox(
        visibleSize,
        PhysicsMaterial(1, 0.5, 0.5),
        5
        );

    boundingBox->setDynamic(false);

    auto edgeNode = Node::create();

    edgeNode->addComponent(boundingBox);
    edgeNode->setPosition(visibleSize / 2);
    addChild(edgeNode);


    getPhysicsWorld()->setGravity(Vec2(0, -200));

    // 
    /*phep & tren bit
        0001
        0011
        0001
           1*/

        /*chuyen tu nhi phan sang thap phan:
        0010 = 2
        0011 = 1 + 2 = 3
        1011 = 1 + 2 + 8 = 11*/

        /*0010 & 0010 > 0
        0001 & 0001 > 0

        category1 & collision2> 0
        &&
        category2 & collision1 > 0*/

    // Draw debug
    getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    this->startPoint = Vec2::ZERO;
    scheduleUpdate();
    return true;
}

void Lesson6::update(float dt) {
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
}


void Lesson6::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();
    //this->mySprite->setPosition(location); 
    this->startPoint = location;
}

void Lesson6::onMouseUp(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();
    Vec2 endPoint = location;
    auto direction = endPoint - startPoint;
    direction.normalize();

    mySprite->getPhysicsBody()->setVelocity(100 * direction);
}

void Lesson6::onMouseMove(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto location = e->getLocationInView();
}

void Lesson6::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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
void Lesson6::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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

bool Lesson6::onContactBegin(cocos2d::PhysicsContact& contact) {
    if ((contact.getShapeA()->getCategoryBitmask() &
        contact.getShapeB()->getCollisionBitmask()) <= 0
        ||
        (contact.getShapeB()->getCategoryBitmask() &
        contact.getShapeA()->getCollisionBitmask()) <= 0) {
        return false;
    }

    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {
        nodeA->setColor(Color3B::RED);
        nodeB->setColor(Color3B::RED);
    }

    return true;
}

void Lesson6::onContactSeparate(cocos2d::PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB) {
        nodeA->setColor(Color3B::WHITE);
        nodeB->setColor(Color3B::WHITE);
    }
}