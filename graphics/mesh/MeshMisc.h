//
// Created by myself on 1/9/20.
//

#ifndef PANORAMA_MESHMISC_H
#define PANORAMA_MESHMISC_H

#include "../../thirdParties/glm/glm/glm.hpp"
#include <string>

struct Vertex {
    // position
    glm::vec3 position;
    // normal
    glm::vec3 normal;
    // texCoords
    glm::vec2 texCoords;
    //  tangent
    glm::vec3 tangent;
    //  bitangent
    glm::vec3 bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

#endif //PANORAMA_MESHMISC_H
