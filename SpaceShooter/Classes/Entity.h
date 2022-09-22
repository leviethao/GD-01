#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

class Entity {
private:
protected:
	cocos2d::Sprite* sprite;
	cocos2d::PhysicsBody* body;
	cocos2d::Vec2 direction;
	float speed;
public:
	Entity();
	Entity(const std::string& filename);
	~Entity();

	cocos2d::Sprite* getSprite();
};

#endif