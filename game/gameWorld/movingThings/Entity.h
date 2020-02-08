//
// Created by myself on 1/18/20.
//

#ifndef PANORAMA_ENTITY_H
#define PANORAMA_ENTITY_H

#include "Point.h"
#include "../../../thirdParties/glm/glm/vec3.hpp"

//  entity is a drawable Point, must add render-specific methods
class Entity {
public:
    Entity(glm::vec3 pos) : position(pos) {}
    virtual glm::vec3 getColor() = 0;

    void addPosition(glm::vec3 posToAdd);
    virtual void addSpeed(glm::vec3 speedToAdd) = 0;
    virtual void addAcceleration(glm::vec3 accToAdd) = 0;
    virtual void addSpeedMod(std::function<glm::vec3(float)> positionFunction) = 0;
    glm::vec3 getPos();

protected:
    glm::vec3 position;
};


#endif //PANORAMA_ENTITY_H
