//
// Created by myself on 12/26/19.
//

#include <malloc.h>
#include <cmath>
#include <cstring>
#include <GL/glew.h>
#include "Mesh.h"


/*
Mesh::Mesh(MESH_GENERATION_STRATEGY strategy) {
    if(strategy != SKYBLOCK_SPHERE)
        return;

    //  get Icosahedron
    elements = (double*)malloc(sizeof(double) * 3 * 20);
    double diameter = 64000.;
    double t = 1.618033989;
    double tm = 1. / sqrt(1. + t*t);
    double vert[12][3] = {
            {tm*t, tm, 0},
            {tm*-t, tm, 0},
            {tm*t, -tm, 0},
            {tm*-t, -tm, 0},
            {tm, 0, tm*t},
            {tm, 0, tm*-t},
            {-tm, 0, tm*t},
            {-tm, 0, tm*-t},
            {0, tm*t, tm},
            {0, tm*-t, tm},
            {0, tm*t, tm*-t},
            {0, tm*-t, -tm},
    };

    //  t0
    memcpy(&elements[0], &vert[0], sizeof(double) * 3);
    memcpy(&elements[1], &vert[8], sizeof(double) * 3);
    memcpy(&elements[2], &vert[4], sizeof(double) * 3);
    //  t1
    memcpy(&elements[0], &vert[0], sizeof(double) * 3);
    memcpy(&elements[5], &vert[0], sizeof(double) * 3);
    memcpy(&elements[10], &vert[0], sizeof(double) * 3);
    //  t2
    memcpy(&elements[2], &vert[0], sizeof(double) * 3);
    memcpy(&elements[4], &vert[0], sizeof(double) * 3);
    memcpy(&elements[9], &vert[0], sizeof(double) * 3);
    //  t3
    memcpy(&elements[2], &vert[0], sizeof(double) * 3);
    memcpy(&elements[11], &vert[0], sizeof(double) * 3);
    memcpy(&elements[5], &vert[0], sizeof(double) * 3);
    //  t4
    memcpy(&elements[1], &vert[0], sizeof(double) * 3);
    memcpy(&elements[6], &vert[0], sizeof(double) * 3);
    memcpy(&elements[8], &vert[0], sizeof(double) * 3);
    //  t5
    memcpy(&elements[1], &vert[0], sizeof(double) * 3);
    memcpy(&elements[10], &vert[0], sizeof(double) * 3);
    memcpy(&elements[7], &vert[0], sizeof(double) * 3);
    //  t6
    memcpy(&elements[3], &vert[0], sizeof(double) * 3);
    memcpy(&elements[9], &vert[0], sizeof(double) * 3);
    memcpy(&elements[6], &vert[0], sizeof(double) * 3);
    //  t7
    memcpy(&elements[3], &vert[0], sizeof(double) * 3);
    memcpy(&elements[7], &vert[0], sizeof(double) * 3);
    memcpy(&elements[11], &vert[0], sizeof(double) * 3);
    //  t8
    memcpy(&elements[0], &vert[0], sizeof(double) * 3);
    memcpy(&elements[10], &vert[0], sizeof(double) * 3);
    memcpy(&elements[8], &vert[0], sizeof(double) * 3);
    //  t9
    memcpy(&elements[1], &vert[0], sizeof(double) * 3);
    memcpy(&elements[8], &vert[0], sizeof(double) * 3);
    memcpy(&elements[10], &vert[0], sizeof(double) * 3);
    //  t10
    memcpy(&elements[2], &vert[0], sizeof(double) * 3);
    memcpy(&elements[9], &vert[0], sizeof(double) * 3);
    memcpy(&elements[11], &vert[0], sizeof(double) * 3);
    //  t11
    memcpy(&elements[3], &vert[0], sizeof(double) * 3);
    memcpy(&elements[9], &vert[0], sizeof(double) * 3);
    memcpy(&elements[11], &vert[0], sizeof(double) * 3);
    //  t12
    memcpy(&elements[4], &vert[0], sizeof(double) * 3);
    memcpy(&elements[2], &vert[0], sizeof(double) * 3);
    memcpy(&elements[0], &vert[0], sizeof(double) * 3);
    //  t13
    memcpy(&elements[5], &vert[0], sizeof(double) * 3);
    memcpy(&elements[0], &vert[0], sizeof(double) * 3);
    memcpy(&elements[2], &vert[0], sizeof(double) * 3);
    //  t14
    memcpy(&elements[6], &vert[0], sizeof(double) * 3);
    memcpy(&elements[1], &vert[0], sizeof(double) * 3);
    memcpy(&elements[3], &vert[0], sizeof(double) * 3);
    //  t15
    memcpy(&elements[7], &vert[0], sizeof(double) * 3);
    memcpy(&elements[3], &vert[0], sizeof(double) * 3);
    memcpy(&elements[1], &vert[0], sizeof(double) * 3);
    //  t16
    memcpy(&elements[8], &vert[0], sizeof(double) * 3);
    memcpy(&elements[6], &vert[0], sizeof(double) * 3);
    memcpy(&elements[4], &vert[0], sizeof(double) * 3);
    //  t17
    memcpy(&elements[9], &vert[0], sizeof(double) * 3);
    memcpy(&elements[4], &vert[0], sizeof(double) * 3);
    memcpy(&elements[6], &vert[0], sizeof(double) * 3);
    //  t18
    memcpy(&elements[10], &vert[0], sizeof(double) * 3);
    memcpy(&elements[5], &vert[0], sizeof(double) * 3);
    memcpy(&elements[7], &vert[0], sizeof(double) * 3);
    //  t19
    memcpy(&elements[11], &vert[0], sizeof(double) * 3);
    memcpy(&elements[7], &vert[0], sizeof(double) * 3);
    memcpy(&elements[5], &vert[0], sizeof(double) * 3);


}*/


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // now that we have all the required data, set the vertex buffers and its attribute pointers.
    setupMesh();
}


void Mesh::Draw(Shader shader) {
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    //  unsigned int normalNr   = 1;
    //  unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
            /*
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream
             */

        // now set the sampler to the correct texture unit
        shader.setFloat(("material." + name + number).c_str(), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}


void Mesh::setupMesh() {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    /*
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    */
    glBindVertexArray(0);
}


