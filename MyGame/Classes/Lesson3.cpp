#include "Lesson3.h"

USING_NS_CC;

Scene* Lesson3::createScene()
{
    return Lesson3::create();
}


// on "init" you need to initialize your instance
bool Lesson3::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->mySprite = Sprite::create("images/Star.png");
    this->mySprite->setPosition(200, 100);
    addChild(this->mySprite);


    /*auto moveTo = MoveTo::create(2, Vec2(500, 500));
    moveTo->setTag(100);
    this->mySprite->runAction(moveTo);*/

    /*auto moveBy = MoveBy::create(2, Vec2(50, 100));
    this->mySprite->runAction(moveBy);*/

    /*this->mySprite->setOpacity(0);
    auto fadeIn = FadeIn::create(2);
    this->mySprite->runAction(fadeIn);*/

    /*auto fadeOut = FadeOut::create(2);
    this->mySprite->runAction(fadeOut);*/


    //scheduleOnce([&](float dt) {
    //    log("Call Stop Move");
    //    //this->mySprite->stopAllActions();
    //    this->mySprite->stopActionByTag(100);
    //}, 1, "stopMove");



    // Sequence
    auto moveTo = MoveTo::create(2, Vec2(300, 300));
    auto rotateBy = RotateBy::create(2, 360);
    auto moveBy = MoveBy::create(2, Vec2(0, -200));
    auto moveFinishCallback = CallFunc::create([&]() {
        log("Finish Move To");
        this->mySprite->setColor(Color3B(255, 0, 0));
    });

    auto delay = DelayTime::create(2);

    /*auto sequence = Sequence::create(moveTo, moveFinishCallback, delay, rotateBy, moveBy, nullptr);
    this->mySprite->runAction(sequence);*/
    //this->mySprite->runAction(sequence->reverse());

    /*auto spawn = Spawn::create(moveTo, rotateBy, nullptr);
    this->mySprite->runAction(spawn);*/
    
    /*this->mySprite->runAction(moveBy);
    this->mySprite->runAction(moveBy->clone());*/

    /*auto easeBounceIn = EaseBounceIn::create(moveTo->clone());
    this->mySprite->runAction(easeBounceIn);*/



    // Custom moveTo
    duration = 2;
    position = Vec2(300, 100);
    startPosition = this->mySprite->getPosition();
    elapseTime = 0;








    scheduleUpdate();
    return true;
}

void Lesson3::update(float dt) {


    // Custom moveTo
    if (elapseTime >= duration) return;
    float distance = startPosition.distance(position);
    float speed = distance / duration;
    direction = position - startPosition;
    direction.normalize(); // length = 1

    auto currentPos = this->mySprite->getPosition();
    this->mySprite->setPosition(currentPos + speed * dt * direction);
    elapseTime += dt;








    //// Action move sprite
    //float speed = 100;
    //Vec2 newPosition = Vec2(this->mySprite->getPosition().x + speed * dt,
    //    this->mySprite->getPosition().y);
    //this->mySprite->setPosition(newPosition);

    ////Action rotate sprite
    //float currentRotation = this->mySprite->getRotation();
    //float rotateSpeed = 30;
    //this->mySprite->setRotation(currentRotation + rotateSpeed * dt);

    // Action scale sprite
    /*float scaleSpeed = 0.5;
    float currentScale = this->mySprite->getScale();
    if (currentScale <= 0) {
        this->mySprite->setScale(0);
    }
    else {
        this->mySprite->setScale(currentScale - scaleSpeed * dt);
    }*/
}
