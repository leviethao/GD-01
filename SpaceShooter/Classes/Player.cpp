#include "Player.h"

USING_NS_CC;

Player::Player():Entity("CloseNormal.png") {
    initListeners();
    this->speed = 100;
    
    // override body
    this->sprite->removeComponent(this->body);
    this->body = PhysicsBody::createCircle(this->sprite->getContentSize().width / 2);
    this->sprite->addComponent(body);
}

Player::~Player() {

}

void Player::initListeners() {
    // Keyboard event listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    this->sprite->getEventDispatcher()
        ->addEventListenerWithSceneGraphPriority(keyboardListener,
            this->sprite);
}


void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
        direction.x = -1;
        break;
    case EventKeyboard::KeyCode::KEY_D:
        direction.x = 1;
        break;
    case EventKeyboard::KeyCode::KEY_S:
        direction.y = -1;
        break;
    case EventKeyboard::KeyCode::KEY_W:
        direction.y = 1;
        break;
    default:
        break;
    }

    direction.normalize();
    this->body->setVelocity(speed * direction);
}
void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_D:
        direction.x = 0;
        break;
    case EventKeyboard::KeyCode::KEY_S:
    case EventKeyboard::KeyCode::KEY_W:
        direction.y = 0;
        break;
    default:
        break;
    }

    direction.normalize();
    this->body->setVelocity(speed * direction);
}