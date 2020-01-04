//
// Created by axiom on 6/23/19.
//

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "../../mathematics/matrices/Matrics.hpp"
#include "../../mathematics/glm_c_wrapper.hpp"
#include "../Game.hpp"


void runInput(Game* game){
    //consts
    // todo: turn everything into radians
    float mouseSens = 0.005f;
    //  static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - game->game.gameProps.lastCycleTime);

    //  MOUSE INPUT
    double xpos, ypos;
    glfwGetCursorPos(game->graph.window, &xpos, &ypos);
    glfwSetCursorPos(game->graph.window, (float)game->graph.winProperties.size.x/2.0f, (float)game->graph.winProperties.size.y/2.0f);

    //  player view angles
    game->game.player.horizontalAngle += mouseSens * deltaTime * (float)(game->graph.winProperties.size.x/2.0f - xpos);
    game->game.player.vertivalAngle += mouseSens * deltaTime * (float)(game->graph.winProperties.size.y/2.0f - ypos);

    Vector3f direction = Vector3fVal(
            cosf(game->game.player.vertivalAngle) * sinf(game->game.player.horizontalAngle),
            sinf(game->game.player.vertivalAngle),
            cosf(game->game.player.vertivalAngle) * cosf(game->game.player.horizontalAngle)
    );

    game->game.player.view.x = cosf(game->game.player.vertivalAngle) * sinf(game->game.player.horizontalAngle) + game->game.player.pos.x;
    game->game.player.view.y = sinf(game->game.player.vertivalAngle) + game->game.player.pos.y;
    game->game.player.view.z = cosf(game->game.player.horizontalAngle) * cosf(game->game.player.vertivalAngle) + game->game.player.pos.z;



    Vector3f right = Vector3fVal(
            sinf(game->game.player.horizontalAngle - (float)M_PI / 2.0f),
            0.0f,
            cosf(game->game.player.horizontalAngle - (float)M_PI / 2.0f)
    );

    Vector3f up = Vec3fCrossR(&right, &direction);



    {//  read KEYBOARD INPUT
        if (glfwGetKey(game->graph.window, GLFW_KEY_W) == GLFW_PRESS)
            game->game.player.pos = vec3fAdd(&game->game.player.pos,
                                             vec3fMulV(&direction, deltaTime * game->game.player.speed));
        if (glfwGetKey(game->graph.window, GLFW_KEY_S) == GLFW_PRESS)
            game->game.player.pos = vec3fSub(game->game.player.pos,
                                             vec3fMulV(&direction, deltaTime * game->game.player.speed));
        if (glfwGetKey(game->graph.window, GLFW_KEY_A) == GLFW_PRESS)
            game->game.player.pos = vec3fAdd(&game->game.player.pos,
                                             vec3fMulV(&right, deltaTime * game->game.player.speed));
        if (glfwGetKey(game->graph.window, GLFW_KEY_D) == GLFW_PRESS)
            game->game.player.pos = vec3fSub(game->game.player.pos,
                                             vec3fMulV(&right, deltaTime * game->game.player.speed));
        if (glfwGetKey(game->graph.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            game->game.isRunning = GL_FALSE;
    }

    //  matices calculation
    //  preformed here only, writes result into : game->graph.winProperties.view


    /* game->graph.winProperties.projection = matrics4fPerspective(game->game.player.initialFOV,
                                                                   (float)game->graph.winProperties.size.x / game->graph.winProperties.size.y,
                                                                   0.1f,
                                                                   4096.0f);     // call this only on resize
    //  game->graph.winProperties.view = Matrics4f_cam(game->game.player.pos, vec3fAdd(&game->game.player.pos, direction), up);
     */

    Matrics4f projection;

    getPerspectiveMatrix_Wrapper(projection.v, game->game.player.initialFOV, game->graph.winProperties.size.x / game->graph.winProperties.size.y, 0.01f, 10245.f);
    getViewMatrix_Wrapper(game->graph.winProperties.view.v,&game->game.player.pos, &game->game.player.view, &up, projection.v);


    game->game.gameProps.lastCycleTime = currentTime;

}
