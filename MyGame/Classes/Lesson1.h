#ifndef __LESSON1_H__
#define __LESSON1_H__

#pragma once;

#include "cocos2d.h"

class Lesson1 : public cocos2d::Scene
{
private:
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson1);
};

#endif // __Lesson1_H__
