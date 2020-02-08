//
// Created by myself on 1/15/20.
//

#ifndef PANORAMA_GGRAPH_H
#define PANORAMA_GGRAPH_H

#include <GLFW/glfw3.h>
#include "../../graphics/mesh/Mesh.h"
#include "../../graphics/window/Window.hpp"
#include "../../graphics/model/Model.h"


class GGraph {
public:
    GGraph();

    GLFWwindow* window;
    WindowProperties winProperties;
    GLint matrixID;

    Shader shader;
    Model model;

    GLuint texture;
    GLint textureID;
    GLfloat* uvBuffer;
    GLuint uvbuffer;

    GLuint* VertexArrayIDs;
    int takenVertexNumber = 0;
    GLuint vertexBuffer;


};
#endif //PANORAMA_GGRAPH_H
