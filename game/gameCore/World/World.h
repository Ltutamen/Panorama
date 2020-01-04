//
// Created by myself on 12/26/19.
//

#ifndef PANORAMA_WORLD_H
#define PANORAMA_WORLD_H


#include "../../../graphics/mesh/Mesh.h"


class World {
public:
    void addMesh(Mesh* mesh);
    World();

private:
    Mesh* meshArr;

};


#endif //PANORAMA_WORLD_H
