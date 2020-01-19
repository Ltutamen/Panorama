//
// Created by myself on 1/18/20.
//

#ifndef PANORAMA_ENTITY_H
#define PANORAMA_ENTITY_H

#include "Point.h"
#include "../../../thirdParties/glm/glm/vec3.hpp"

//  entity is a drawable Point, must add render-specific methods
class Entity : public Point {
public:
    Entity(glm::vec3 pos) : Point(pos) {}
    virtual glm::vec3 getColor() = 0;


    void addPosition(glm::vec3 posToAdd) override ;
    void addSpeed(glm::vec3 speedToAdd) override;
    void addAcceleration(glm::vec3 accToAdd) override;
    void addSpeedMod(std::function<glm::vec3(float)> positionFunction) override;

    float movementSpeedMultiplier;
protected:
};


#endif //PANORAMA_ENTITY_H
