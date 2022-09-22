#ifndef __LESSON9_SCENE_H__
#define __LESSON9_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"

class Lesson9 : public cocos2d::Scene
{
public:
    int backgroundMusic;
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Lesson9);
};

#endif // __LESSON9_SCENE_H__
