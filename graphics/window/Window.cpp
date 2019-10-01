//
// Created by axiom on 4/10/19.
//

#include <malloc.h>
#include "Window.hpp"
#include "../shaders/Shader.hpp"

WindowProperties * newWindowProperties(){
    auto* window = (WindowProperties*)malloc(sizeof(WindowProperties));

    window->size.x = 1280;
    window->size.y = 800;
    window->pos.x = 50;
    window->pos.y = 50;

    window->backColor[0] = 0.0f;
    window->backColor[1] = 0.2f;
    window->backColor[2] = 0.0f;
    window->backColor[3] = 1.0f;


    return window;
}
