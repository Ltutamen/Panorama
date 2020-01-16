//
// Created by axiom on 5/1/19.
//

#include <malloc.h>
#include "Player.hpp"


Player::Player(){

    this->pos = *newVector3f(100.0f, 100.0f, 100.0f );
    this->view = *newVector3f(1.0f ,1.0f, 1.0f );
    this->horizontalAngle = 3.14f;
    this->vertivalAngle = 0.0f;
    this->initialFOV = 3.145f / 2.f;
    this->speed = 300.0f;
    this->mouseSpeed = 0.005f;

}
