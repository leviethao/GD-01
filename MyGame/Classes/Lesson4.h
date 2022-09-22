#ifndef __LESSON4_H__
#define __LESSON4_H__

#include "cocos2d.h"

class Lesson4 : public cocos2d::Scene
{
private:
    cocos2d::Sprite* mySprite;
    cocos2d::Vec2 direction;
    float speed;
    bool isDrag;
    cocos2d::Vec2 aimDirection;
    std::vector<cocos2d::Sprite*> bulletList;
    std::vector<cocos2d::Sprite*> enemyList;

    void onMouseDown(cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);
    void onMouseMove(cocos2d::Event* event);
    void onMouseScroll(cocos2d::Event* event);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void spawnEnemy();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Lesson4);
};

#endif // __Lesson4_H__
