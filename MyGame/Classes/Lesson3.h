#ifndef __LESSON3_H__
#define __LESSON3_H__

#include "cocos2d.h"

class Lesson3 : public cocos2d::Scene
{
private:
    cocos2d::Sprite* mySprite;
    float duration;
    cocos2d::Vec2 startPosition;
    cocos2d::Vec2 position;
    cocos2d::Vec2 direction;
    float elapseTime;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson3);
};

#endif // __Lesson3_H__
