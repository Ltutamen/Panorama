//
// Created by axiom on 4/10/19.
//

#ifndef DYNAMICOCTTREE_CI_WINDOW_H
#define DYNAMICOCTTREE_CI_WINDOW_H

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "../../game/mathematics/matrices/Matrics.hpp"
#include "../../thirdParties/glm/glm/glm.hpp"

typedef struct {
    GLFWwindow* window;

    Vector2ui size;
    Vector2ui pos;

    GLfloat backColor[4];

    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;

    GLuint program;


} WindowProperties;

WindowProperties newWindowProperties();


#endif //DYNAMICOCTTREE_CI_WINDOW_H
