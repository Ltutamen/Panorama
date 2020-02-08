//
// Created by axiom on 5/1/19.
//

#ifndef DYNAMICOCTTREE_CI_PLAYER_H
#define DYNAMICOCTTREE_CI_PLAYER_H

#include "../../../mathematics/vectors/Vectors.hpp"
#include "../Entity.h"
#include "../../../../graphics/camera/Camera.h"
#include "../FixedEntity.h"


class Player : public FixedEntity {
public:
    Player(glm::vec3 pos);

    //  todo inherit from camera
    glm::vec3 view;
    float horizontalAngle;
    float verticalAngle;
    float initialFOV;

    float movementSpeedMultiplier;

    Camera camera;

    glm::vec3 getColor() override;

    void addSpeed(glm::vec3 speedToAdd) override;

    void addAcceleration(glm::vec3 accToAdd) override;

    void addSpeedMod(std::function<glm::vec3(float)> positionFunction) override;



};



#endif //DYNAMICOCTTREE_CI_PLAYER_H
