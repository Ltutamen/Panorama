//
// Created by myself on 12/26/19.
//

#ifndef PANORAMA_MESH_H
#define PANORAMA_MESH_H

enum MESH_GENERATION_STRATEGY{SPHERE, SKYBLOCK_SPHERE};

//  todo make interface
class Mesh {
public:
    //  number of 3-dPOINTS in mesh, real size is 3 times bigger
    unsigned long size;
    double* elements;

    virtual ~Mesh();

    Mesh(MESH_GENERATION_STRATEGY strategy);


private:

};


#endif //PANORAMA_MESH_H
