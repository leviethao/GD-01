#ifndef __LESSON6_H__
#define __LESSON6_H__

#include "cocos2d.h"

class Lesson6 : public cocos2d::Scene
{
private:
    cocos2d::Sprite* mySprite;
    cocos2d::Vec2 direction;
    float speed;
    cocos2d::Vec2 startPoint;

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onContactSeparate(cocos2d::PhysicsContact& contact);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson6);
};

#endif // __Lesson6_H__
