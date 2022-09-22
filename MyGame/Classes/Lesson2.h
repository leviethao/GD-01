#ifndef __LESSON2_H__
#define __LESSON2_H__

#include "cocos2d.h"

class Lesson2 : public cocos2d::Scene
{
private:
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson2);
};

#endif // __Lesson2_H__
