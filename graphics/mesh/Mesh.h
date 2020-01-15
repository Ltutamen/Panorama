//
// Created by myself on 12/26/19.
//

#ifndef PANORAMA_MESH_H
#define PANORAMA_MESH_H

#include "MeshMisc.h"
#include "../shaders/Shader.hpp"
#include <vector>

enum MESH_GENERATION_STRATEGY{SPHERE, SKYBLOCK_SPHERE};


//  todo make interface
class Mesh {
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    /*  Functions  */
    // constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    // render the mesh
    void Draw(Shader shader);
private:
    /*  Render data  */
    unsigned int VBO, EBO;
    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh();

};


#endif //PANORAMA_MESH_H
