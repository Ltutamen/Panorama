//
// Created by myself on 2/1/20.
//

#ifndef PANORAMA_MODEL_H
#define PANORAMA_MODEL_H


#include <assimp/material.h>
#include <assimp/scene.h>
#include "../shaders/Shader.hpp"
#include "../mesh/Mesh.h"

class Model {
public:
    Model(std::string path);

    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    void Draw(Shader shader);

private:

    /*  Functions   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                         std::string typeName);

};


#endif //PANORAMA_MODEL_H
