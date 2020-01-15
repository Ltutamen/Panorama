//
// Created by myself on 1/9/20.
//

#ifndef PANORAMA_MESHMISC_H
#define PANORAMA_MESHMISC_H

#include "../../thirdParties/glm/glm/glm.hpp"
#include <string>

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

#endif //PANORAMA_MESHMISC_H
