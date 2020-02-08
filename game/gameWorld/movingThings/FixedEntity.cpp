//
// Created by myself on 2/2/20.
//

#include "FixedEntity.h"


FixedEntity::FixedEntity(glm::vec3 pos) : Entity(pos) {
    this->up = glm::vec3(0.f, 1.f, 0.f);
    this->right = glm::vec3(1.f, 0.f, 0.f);
    this->front = glm::vec3(0.2f, 0.2f, 0.2f);
}


glm::vec3 FixedEntity::getColor() {
    return glm::vec3();
}


void FixedEntity::addSpeed(glm::vec3 speedToAdd) {

}


void FixedEntity::addAcceleration(glm::vec3 accToAdd) {

}


void FixedEntity::addSpeedMod(std::function<glm::vec3(float)> positionFunction) {

}
