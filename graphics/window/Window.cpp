//
// Created by axiom on 4/10/19.
//

#include "Window.hpp"
#include "../shaders/Shader.hpp"
#include "../../thirdParties/glm/glm/gtc/matrix_transform.hpp"


//  todo delete
WindowProperties newWindowProperties(){
    WindowProperties window;

    window.size.x = 1280;
    window.size.y = 800;
    window.pos.x = 50;
    window.pos.y = 50;

    window.backColor[0] = 0.0f;
    window.backColor[1] = 0.2f;
    window.backColor[2] = 0.0f;
    window.backColor[3] = 1.0f;

    window.projection = glm::perspective(glm::radians(3.14f), 1280.0f / 800.0f, 0.01f, 10245.0f);

    window.view = glm::lookAt(glm::vec3(512.0f, 512.0f, 512.0f),
                              glm::vec3(514.0f, 515.0f, 516.0f),
                              glm::vec3(212.0f, 312.0f, 412.0f));   //0todo original view parametres

    window.model = glm::mat4(1.f);

    window.program = makeShaderProgram("../graphics/shaders/fragment001.fs",
                                       "../graphics/shaders/vertex001.vs");
    return window;
}
