//
// Created by axiom on 5/1/19.
//

#ifndef DYNAMICOCTTREE_CI_PLAYER_H
#define DYNAMICOCTTREE_CI_PLAYER_H

#include "../../../mathematics/vectors/Vectors.hpp"
#include "../Entity.h"

class Player : public Entity {
public:
    Player();

    //  todo inherit from camera
    glm::vec3 view;
    float horizontalAngle;
    float verticalAngle;
    float initialFOV;

    glm::vec3 getColor() override;

    void addSpeed(glm::vec3 speedToAdd) override;

    void addAcceleration(glm::vec3 accToAdd) override;

    void addSpeedMod(std::function<glm::vec3(float)> positionFunction) override;

};



#endif //DYNAMICOCTTREE_CI_PLAYER_H
