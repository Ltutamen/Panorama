//
// Created by myself on 1/18/20.
//

#ifndef PANORAMA_POINT_H
#define PANORAMA_POINT_H


#include <functional>
#include "../../../thirdParties/glm/glm/vec3.hpp"


class Point {
public:
    Point(glm::vec3 pos) :
        position(pos),
        speed(glm::vec3{0.f, 0.f, 0.f}),
        acceleration {glm::vec3{0.f, 0.f, 0.f}}
        {};


    virtual void addPosition(glm::vec3 posToAdd) = 0;
    virtual void addSpeed(glm::vec3 speedToAdd) = 0;
    virtual void addAcceleration(glm::vec3 accToAdd) = 0;
    virtual void addSpeedMod(std::function<glm::vec3(float)> positionFunction) = 0;

    glm::vec3 getPos() { return position; }

protected:
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 acceleration;
};


#endif //PANORAMA_POINT_H
