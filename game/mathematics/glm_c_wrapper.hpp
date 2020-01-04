//
// Created by axiom on 8/14/19.
//
#ifndef PANORAMA_GLM_C_WRAPPER_H
#define PANORAMA_GLM_C_WRAPPER_H


//#include "vectors/Vectors.h"

#include "vectors/Vectors.hpp"

void getPerspectiveMatrix_Wrapper(float *result, float FOV, float ratio, float near, float far);
void getViewMatrix_Wrapper(float *result, Vector3f *eye, Vector3f *view, Vector3f *head, float *perspectiveM);

#endif //PANORAMA_GLM_C_WRAPPER_H
