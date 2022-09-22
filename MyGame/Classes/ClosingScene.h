#ifndef __CLOSING_SCENE_H__
#define __CLOSING_SCENE_H__

#include "cocos2d.h"

class ClosingScene : public cocos2d::Scene
{
private:
public:
    static cocos2d::Scene* createScene(int _score);

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ClosingScene);
};

#endif // __CLOSING_SCENE_H__
