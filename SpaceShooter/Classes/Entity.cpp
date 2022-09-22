#include "Entity.h"

USING_NS_CC;

Entity::Entity() {

}

Entity::Entity(const std::string& filename) {
	this->sprite = Sprite::create(filename);
	this->body = PhysicsBody::createBox(this->sprite->getContentSize());
	this->sprite->addComponent(body);
	this->direction = Vec2::ZERO;
	this->speed = 0;
}

Entity::~Entity() {

}

Sprite* Entity::getSprite() {
	return this->sprite;
}