#ifndef __LESSON7_H__
#define __LESSON7_H__

#include "cocos2d.h"

class Lesson7 : public cocos2d::Scene
{
private:
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void initUI();

    CREATE_FUNC(Lesson7);
};

#endif // __Lesson7_H__
