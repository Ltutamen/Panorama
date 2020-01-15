//
// Created by myself on 1/15/20.
//

#ifndef PANORAMA_GGRAPH_H
#define PANORAMA_GGRAPH_H

#include <GLFW/glfw3.h>
#include "../../graphics/mesh/Mesh.h"
#include "../../graphics/window/Window.hpp"


class GGraph {
public:
    GLFWwindow* window;
    WindowProperties winProperties;
    GLint matrixID;

    GLuint texture;
    GLint textureID;
    GLfloat* uvBuffer;
    GLuint uvbuffer;

    GLuint* VertexArrayIDs;
    int takenVertexNumber = 0;
    GLuint vertexBuffer;

    void addMesh(Mesh* mesh);
};
#endif //PANORAMA_GGRAPH_H
