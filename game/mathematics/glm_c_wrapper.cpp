//
// Created by axiom on 8/14/19.
//

#include "../../thirdParties/glm/glm/glm.hpp"
#include "../../thirdParties/glm/glm/gtc/matrix_transform.hpp"

using namespace glm;


void getPerspectiveMatrix_Wrapper(float* result, float FOV, float ratio, float near, float far){

    glm::mat4 Projection = glm::perspective(glm::radians(FOV), ratio, near, far);
    for(int i=0 ; i<4 ; ++i) {
        result[i * 4 + 0] = Projection[i][0];
        result[i * 4 + 1] = Projection[i][1];
        result[i * 4 + 2] = Projection[i][2];
        result[i * 4 + 3] = Projection[i][3];
    }
}


void getViewMatrix_Wrapper(float* result, glm::vec3 eye, glm::vec3 view, glm::vec3 head, float* perspectiveM){

    glm::mat4 Model = glm::mat4(1.f);

    glm::mat4 View = glm::lookAt(
            glm::vec3(eye.x, eye.y, eye.z),
            glm::vec3(view.x, view.y, view.z),
            glm::vec3(head.x, head.y, head.z));

    glm::mat4 Perspective = glm::mat4(perspectiveM[0], perspectiveM[1], perspectiveM[2], perspectiveM[3],
                          perspectiveM[4], perspectiveM[5], perspectiveM[6], perspectiveM[7],
                          perspectiveM[8], perspectiveM[9], perspectiveM[10], perspectiveM[11],
                          perspectiveM[12], perspectiveM[13], perspectiveM[14], perspectiveM[15]);

    glm::mat4 MVP = Perspective * View * Model;

    for(int i=0 ; i<4 ; ++i) {
        result[i * 4 + 0] = MVP[i][0];
        result[i * 4 + 1] = MVP[i][1];
        result[i * 4 + 2] = MVP[i][2];
        result[i * 4 + 3] = MVP[i][3];
    }
}