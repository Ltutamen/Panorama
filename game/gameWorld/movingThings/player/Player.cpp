//
// Created by axiom on 5/1/19.
//

#include <malloc.h>
#include "Player.hpp"


Player::Player() : Entity(glm::vec3{1.0f, 1.0f, 1.0f}) {

    this->view = glm::vec3(1.f, 1.f, 1.f);
    this->horizontalAngle = 3.14f;
    this->verticalAngle = 0.0f;
    this->initialFOV = 3.145f / 2.f;
    this->movementSpeedMultiplier = 300.0f;

}

glm::vec3 Player::getColor() {
    return glm::vec3(0.5f, 0.5f, 0.5f);
}

void Player::addSpeed(glm::vec3 speedToAdd) {
    this->speed += speedToAdd;
}

void Player::addAcceleration(glm::vec3 accToAdd) {

}

void Player::addSpeedMod(std::function<glm::vec3(float)> positionFunction) {

}
