//
// Created by axiom on 5/1/19.
//

#include <malloc.h>
#include "Player.hpp"


Player* newPlayer(){
    auto* result = (Player*)malloc(sizeof(Player));
    result->pos = *newVector3f(100.0f, 100.0f, 100.0f );
    result->view = *newVector3f(1.0f ,1.0f, 1.0f );
    result->horizontalAngle = 3.14f;
    result->vertivalAngle = 0.0f;
    result->initialFOV = 3.145f / 2.f;
    result->speed = 300.0f;
    result->mouseSpeed = 0.005f;
    return result;
}


Player nPlayer(){
    Player result;
    result.pos = *newVector3f(0.0f ,0.0f, 0.0f );
    result.view = *newVector3f(0.0f ,0.0f, 0.0f );
    result.horizontalAngle = 3.14f;
    result.vertivalAngle = 0.0f;
    result.initialFOV = 3.145f / 2.f;
    result.speed = 3.0f;
    result.mouseSpeed = 0.005f;
    return result;
}