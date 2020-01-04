//
// Created by axiom on 5/10/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>
#include "Matrics.hpp"

Matrics4f Matrics4f_null(){
    return Matrics4fVal(0.0f);
}


Matrics4f Matrics4f_one(){
    return Matrics4fVal(1.0f);
}


Matrics4f* newMatrics4f_null(){
    Matrics4f* result = (Matrics4f*)malloc(sizeof(Matrics4f));
    for(uint i=0 ; i<16 ; i++)
        result->v[i] = 0.0f;

    return result;
}


Matrics4f* newMatrics4f_one(){
    Matrics4f* result = (Matrics4f*)malloc(sizeof(Matrics4f));
    for(uint i=0 ; i<16 ; i++)
        result->v[i] = 1.0f;

    return result;
}


Matrics4f Matrics4fVal(float val){
    Matrics4f result;
    for(uint i=0 ; i<16 ; i++){
        result.v[i] = val;
    }
    return result;
}


Matrics4f Matrics4f_rand(){
    Matrics4f result;
    srand(112);
    for(uint i=0 ; i<16 ; i++){
        result.v[i]   = ((float)rand()/RAND_MAX) * 1.0f;

    }
    return result;
}


void matrics4fPrint(Matrics4f matr){
    putchar('\n');
    for(uint i=0 ; i<4 ; i++){
        for(uint j=0 ; j<4 ; j++){
            printf("\t%3.2f_", matr.v[4*i + j]);
        }
        printf("\n");
    }
}


void matrics4fMult(Matrics4f* result, Matrics4f* arg){
    Matrics4f buffer;
    for(uint i=0 ; i<16 ; i++){
        buffer.v[i] = result->v[i];
        result->v[i] = 0.0f;
    }
    // high-efficiency alg
    float r;

    for(uint i=0 ; i<4 ; i++){
        for(uint k=0 ; k<4 ; k++){
            r = buffer.v[i*4+k];
            for(uint j=0 ; j<4 ; j++)
                result->v[i*4+j] += r * arg->v[k*4+j];   //j*4+i or i*4+j
        }
    }

}


Matrics4f* newMatrics4fMult(Matrics4f* aarg, Matrics4f* barg){
    Matrics4f* result = (Matrics4f*)malloc(sizeof(Matrics4f));

    for(uint i=0 ; i<16 ; i++)
        result->v[i] = aarg->v[i];

    float r;

    for(uint i=0 ; i<4 ; i++){
        for(uint k=0 ; k<4 ; k++){
            r = result->v[k*4+i];
            for(uint j=0 ; j<4 ; j++)
                result->v[i*4+j] += r * barg->v[k*4+j];
        }
    }

    return result;
}


Matrics4f matrics4fPerspective(float fovAngle, float ratio, float near, float far){
    // RH_ZO todo ?
    Matrics4f result = Matrics4f_null();

    float range = tanhf(fovAngle / 2.0f) * near;

    // todo here -> https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix

    /* this
    result.v[0*4+0] = 1.0f / (ratio * tanHalfF);
    result.v[1*4+1] = 1.0f / tanHalfF;
    result.v[2*4+2] = far / (near - far);
    result.v[2*4+3] = 1.0f;
    result.v[3*4+2] = - (far * near) / (far - near);
    */ //or this?
    result.v[0] = 2.f * near / (range * ratio);
    result.v[5] = near / range;
    result.v[10] = - (far + near) / (far - near);  // or ep-1
    result.v[11] = -1.0f;
    result.v[14] = -2.0f * near;

    return result;

}


//                       EYE                       CENTER                  UP
Matrics4f Matrics4f_cam(Vector3f cameraPosition, Vector3f cameraLoockAt, Vector3f headsUp){
    printf("\nCAMPOS: %f %f %f __LOOCK_AT_ %f %f %f __HEADUP: %f %f %f", cameraPosition.x, cameraPosition.y, cameraPosition.z,
           cameraLoockAt.x, cameraLoockAt.y, cameraLoockAt.z,
           headsUp.x, headsUp.y, headsUp.z);
    Matrics4f result = Matrics4f_null();

    Vector3f xaxis, yaxis, zaxis;

    zaxis = vec3fSub(cameraPosition, cameraLoockAt);    //  zaxis -> f vect
    vec3fNormalize(&zaxis);

    {                                                   //  yaxis -> s vect
        yaxis.x = headsUp.x;
        yaxis.y = headsUp.y;
        yaxis.z = headsUp.z;
    }
    yaxis = Vec3fCrossR(&zaxis, &headsUp);
    vec3fNormalize(&yaxis);

    xaxis = Vec3fCrossR(&yaxis, &zaxis);                             //  xaxis -> u vect

    result.v[0] = yaxis.x;
    result.v[4] = yaxis.y;
    result.v[8] = yaxis.z;
    result.v[12] = - vec3fdot(&yaxis, cameraPosition);
    result.v[13] = - vec3fdot(&xaxis, cameraPosition);
    result.v[14] = vec3fdot(&zaxis, cameraPosition);
    result.v[1] = xaxis.x;
    result.v[5] = xaxis.y;
    result.v[9] = xaxis.z;
    result.v[2] = - zaxis.x;
    result.v[6] = - zaxis.y;
    result.v[10] = - zaxis.z;

    //  todo remove
    result.v[3] = 1.0f;
    result.v[7] = 1.0f;
    result.v[11] = 1.0f;
    result.v[15] = 1.0f;

    return result;
}


