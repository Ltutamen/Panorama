//
// Created by myself on 2/2/20.
//

#ifndef PANORAMA_FIXEDENTITY_H
#define PANORAMA_FIXEDENTITY_H


#include "../../../thirdParties/glm/glm/vec3.hpp"
#include "Entity.h"

class FixedEntity : public Entity {
public:
    FixedEntity(glm::vec3 pos);

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    glm::vec3 worldUp;

    glm::vec3 getColor() override;

    void addSpeed(glm::vec3 speedToAdd) override;

    void addAcceleration(glm::vec3 accToAdd) override;

    void addSpeedMod(std::function<glm::vec3(float)> positionFunction) override;

};

#endif //PANORAMA_FIXEDENTITY_H
