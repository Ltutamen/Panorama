//
// Created by axiom on 5/1/19.
//

#include "Player.hpp"


Player::Player(glm::vec3 pos) : FixedEntity(pos), camera(this) {

    this->view = glm::vec3(1.f, 1.f, 1.f);
    this->horizontalAngle = 3.14f;
    this->verticalAngle = 0.0f;
    this->initialFOV = 90.f;
    this->movementSpeedMultiplier = 300.0f;


}


glm::vec3 Player::getColor() {
    return glm::vec3(0.5f, 0.5f, 0.5f);
}


void Player::addSpeed(glm::vec3 speedToAdd) {
    //  this->speed += speedToAdd;
}


void Player::addAcceleration(glm::vec3 accToAdd) {

}


void Player::addSpeedMod(std::function<glm::vec3(float)> positionFunction) {

}
