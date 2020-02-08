//
// Created by myself on 1/18/20.
//

#include "Entity.h"

void Entity::addSpeed(glm::vec3 speedToAdd) {

}

void Entity::addAcceleration(glm::vec3 accToAdd) {

}

void Entity::addSpeedMod(std::function<glm::vec3(float)> positionFunction) {

}

void Entity::addPosition(glm::vec3 posToAdd) {
    this->position += posToAdd;
}

glm::vec3 Entity::getPos() {
    return position;
}
