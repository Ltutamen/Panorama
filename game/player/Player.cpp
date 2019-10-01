//
// Created by axiom on 5/1/19.
//

#include "Player.hpp"

//  todo constuctor to read from save file
Player::Player() {
    this->pos = glm::vec3(100., 100., 100.);
    this->camPos = pos + glm::vec3(0., 0., 1.96);
    this->headsUp = glm::vec3(0., 1., 0.);
    this->view = glm::vec3(0.f, 0.f, 1.f);
    this->fov = 45.0;
    this->horizAngl = 3.14f;
    this->vertAngl = 0.f;
    this->speed = 1.;
    this->mouseSpeed = 1.;
}

Player::~Player() {
    //  nothing to do yet
}
