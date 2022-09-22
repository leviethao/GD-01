#ifndef __LESSON10_SCENE_H__
#define __LESSON10_SCENE_H__

#include "cocos2d.h"

class Lesson10 : public cocos2d::Scene
{
private:
    void onMouseDown(cocos2d::Event* event);
    cocos2d::Sprite* mySprite;
    cocos2d::Animation* animation;
    cocos2d::Animation* createAnimation(std::string prefixName, int pFrameOrder, float delay);
    void initAniamtion();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson10);
};

#endif // __LESSON10_SCENE_H__
