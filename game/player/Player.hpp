//
// Created by axiom on 5/1/19.
//

#ifndef DYNAMICOCTTREE_CI_PLAYER_H
#define DYNAMICOCTTREE_CI_PLAYER_H

#include "../mathematics/vectors/Vectors.hpp"
#include "../../thirdParties/glm/glm/fwd.hpp"
#include "../../thirdParties/glm/glm/detail/type_vec3.hpp"

class Player {
public:
    //  Player position
    glm::vec3 pos;
    //  Player view direction
    glm::vec3 view;
    //  player view point position
    glm::vec3 camPos;

    glm::vec3 headsUp;

    float horizAngl;
    float vertAngl;
    float fov;
    float speed;
    float mouseSpeed;

    Player();
    ~Player();


};

#endif //DYNAMICOCTTREE_CI_PLAYER_H
