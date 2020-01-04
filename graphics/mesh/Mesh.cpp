//
// Created by myself on 12/26/19.
//

#include <malloc.h>
#include <cmath>
#include <cstring>
#include "Mesh.h"


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


}


Mesh::~Mesh() {
    delete elements;
}
