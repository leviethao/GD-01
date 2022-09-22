#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoadingScene : public cocos2d::Scene
{
public:
    cocos2d::ui::LoadingBar* loadingBar;
    static cocos2d::Scene* createScene();
    void allTexturesLoaded(cocos2d::Texture2D* texture);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__
