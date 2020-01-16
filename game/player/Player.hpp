//
// Created by axiom on 5/1/19.
//

#ifndef DYNAMICOCTTREE_CI_PLAYER_H
#define DYNAMICOCTTREE_CI_PLAYER_H

#include "../mathematics/vectors/Vectors.hpp"

class Player {
public:
    Player();
    Vector3f pos;

    //  todo inherit from camera
    Vector3f view;
    float horizontalAngle;
    float vertivalAngle;
    float initialFOV;
    //  todo inherit from entity
    float speed;
    float mouseSpeed;

};



#endif //DYNAMICOCTTREE_CI_PLAYER_H
