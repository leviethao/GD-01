#include "Lesson10.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

const int ACTION_RUN = 1;
const int ACTION_JUMP = 2;

Scene* Lesson10::createScene()
{
    return Lesson10::create();
}


// on "init" you need to initialize your instance
bool Lesson10::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*auto layerBackground = LayerColor::create(Color4B::GRAY);
    addChild(layerBackground);*/

    //auto particleFire = ParticleFire::create();
    //addChild(particleFire);
    //particleFire->setPosition(visibleSize / 2);
    ///*particleFire->setEmitterMode(ParticleSystem::Mode::GRAVITY);
    //particleFire->setGravity(Vec2(30, 30));*/

    //particleFire->setEmitterMode(ParticleSystem::Mode::GRAVITY);
    //particleFire->setGravity(Vec2(0, -50));
    ///*particleFire->setStartRadius(500);
    //particleFire->setEndRadius(0);*/
    ////particleFire->setDuration(2);
    //particleFire->setStartColor(Color4F::BLUE);
    //particleFire->setEndColor(Color4F::ORANGE);
    //particleFire->setAngle(45);


    //
    /*std::vector<ParticleSystem*> particles = {
        ParticleRain::create(),
        ParticleExplosion::create(),
        ParticleFire::create(),
        ParticleFireworks::create(),
        ParticleSun::create(),
        ParticleGalaxy::create(),
        ParticleFlower::create(),
        ParticleMeteor::create(),
        ParticleSpiral::create(),
        ParticleSmoke::create(),
        ParticleSnow::create(),
    };

    auto scrollView = ui::ScrollView::create();
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->setPosition(visibleSize / 2);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    addChild(scrollView);

    scrollView->setContentSize(Size(800, 600));
    scrollView->setInnerContainerSize(Size(800, 3000));

    for (int i = 0; i < particles.size(); i++) {
        particles[i]->setPosition(i % 2 * 400 + 200, int(i / 2) * (-400) + 2200);

        scrollView->addChild(particles[i]);
    }*/

    /*auto my_particle = ParticleSystemQuad::create("particles/particle_texture.plist");
    addChild(my_particle);*/


    this->mySprite = Sprite::create("Player.png");
    this->mySprite->setContentSize(Size(50, 50));
    this->mySprite->setPosition(200, 100);
    addChild(this->mySprite);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(Lesson10::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    initAniamtion();

    return true;
}

void Lesson10::onMouseDown(Event* event) {
    //mySprite->stopAllActions();
    mySprite->stopActionByTag(ACTION_RUN);

    this->animation = createAnimation("Jump", 9, 0.1);
    auto jump = Animate::create(this->animation);
  
    auto action = Sequence::create(jump, CallFunc::create([&]() {
        mySprite->stopActionByTag(ACTION_JUMP);
        this->animation = createAnimation("Run", 8, 0.1);
        auto run = Animate::create(this->animation);
        auto actionRun = RepeatForever::create(run);
        actionRun->setTag(ACTION_RUN);
        mySprite->runAction(actionRun);
        }), nullptr);
    action->setTag(ACTION_JUMP);
    mySprite->runAction(action);
}

Animation* Lesson10::createAnimation(std::string prefixName,
    int pFrameOrder, float delay)
{
    Vector<SpriteFrame*> animFrames;
    for (int i = 1; i <= pFrameOrder; i++) {
        char buffer[20] = { 0 };
        sprintf(buffer, " (%d).png", i);
        std::string imgName = prefixName + buffer; // The name of image in the sprite sheet
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
        animFrames.pushBack(frame);
    }

    auto _animation = Animation::createWithSpriteFrames(animFrames, delay);
    return _animation;
}

void Lesson10::initAniamtion() {
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/animations.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animations/jump.plist");
    
    this->mySprite = Sprite::createWithSpriteFrameName("Run (1).png");
    addChild(mySprite);
    mySprite->setPosition(300, 300);

    this->animation = createAnimation("Run", 8, 0.05);
    auto animate = Animate::create(this->animation);
    auto action = RepeatForever::create(animate);
    action->setTag(ACTION_RUN);
    mySprite->runAction(action);
}