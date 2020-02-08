//
// Created by axiom on 6/11/19.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include <time.h>
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <math.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../graphics/window/Window.hpp"
#include "../../graphics/textures/Texture.hpp"
#include "../mathematics/glm_c_wrapper.hpp"
#include "../../thirdParties/glm/glm/gtc/matrix_transform.hpp"

Game* Game::gameInstance = (Game*)(nullptr);
GLboolean Game::truePtr = GL_TRUE;


long clocksPerFrame;
long clocksPerUpdate;



Game::Game() : game() {
    Vectornf* polys = newVectornf(6 * 3);
    fillPolys(polys->arr);
    //  game = nGGame();
    game.triaBuffer = polys;

    graph.VertexArrayIDs = (GLuint*)malloc(sizeof(GLuint) * 50);

    gameOpenGlInit();


    //uv buffer filling // todo autogen
    graph.uvBuffer = (GLfloat*)malloc(sizeof(GLfloat) * 2 * 6);
    graph.uvBuffer[0] = 0.01f; graph.uvBuffer[1] = 0.01f;
    graph.uvBuffer[2] = 0.01f; graph.uvBuffer[3] = 0.98f;
    graph.uvBuffer[4] = 0.98f; graph.uvBuffer[5] = 0.98f;

    graph.uvBuffer[6] = 0.99f; graph.uvBuffer[7] = 0.99f;
    graph.uvBuffer[8] = 0.99f; graph.uvBuffer[8] = 0.01f;
    graph.uvBuffer[10] = 0.01f; graph.uvBuffer[11] = 0.01f;

    glGenBuffers(1, &graph.uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, graph.uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(graph.uvBuffer), graph.uvBuffer, GL_STATIC_DRAW);

    game.isRunning = GL_TRUE;

}


void Game::initRender() {
    glm::mat4 model(1.f);
    graph.winProperties.view *= model;
    graph.winProperties.projection *= graph.winProperties.view;
    graph.matrixID = glGetUniformLocation(graph.winProperties.program, "MVP");

}


void Game::gameOpenGlInit() {
    if (!glfwInit())
        exit(2);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    graph.winProperties.size.x = 1280;
    graph.winProperties.size.y = 800;
    graph.window = glfwCreateWindow(graph.winProperties.size.x, graph.winProperties.size.y, "Faust\0", NULL, NULL);

    if(!graph.window) {
        Logger::log("ERROR at glfwCreateWindow(...), window failed to create\0");
        exit(1);
    }

    glfwShowWindow(graph.window);
    glfwMakeContextCurrent(graph.window);

    Logger::log("OpenGL Version: \0");
    Logger::log((char*)glGetString(GL_VERSION));
    Logger::log((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    if(glewInit() != GLEW_OK) {
        Logger::log("ERROR: glewInit() is not GLEW_OK in gameOpenGlinit()");
        exit(1);
    }

    glfwSetInputMode(graph.window, GLFW_STICKY_KEYS, GL_TRUE);

    //VAO initialization
    glGenVertexArrays(1, &(graph.VertexArrayIDs[0]));
    glBindVertexArray(graph.VertexArrayIDs[0]);

    //Buffer Creation
    glGenBuffers(1, &graph.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, graph.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * game.triaBuffer->len, game.triaBuffer->arr, GL_STATIC_DRAW);

    graph.winProperties = newWindowProperties();

    graph.matrixID = glGetUniformLocation(graph.winProperties.program, "MWP");

    glfwSetInputMode(graph.window, GLFW_STICKY_KEYS, GL_TRUE);

    graph.texture = loadBMP("../resources/text1.bmp");
    graph.textureID = glGetUniformLocation(graph.winProperties.program, "exampleTexture");

    glfwSetCursorPos(graph.window, (float)graph.winProperties.size.x/2.0f, (float)graph.winProperties.size.y/2.0f);
}


//  runs game loop
void Game::run() {
    initRender();

    clocksPerFrame = CLOCKS_PER_SEC/targetFPS;
    clocksPerUpdate = CLOCKS_PER_SEC/targetUPS;
    long clocksPerUpdateCycle = 0;


    long previous = clock() - clocksPerFrame;
    int i = 0;
    long lag = 0;


    while(*getRunFlagPtr() == GL_TRUE) {
        long current = clock();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        for(uint j = 0 ; lag>=clocksPerUpdateCycle && j<targetUPS ; j++) {
            //runLogick();
            //  putchar('u');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }

        while(lag >= clocksPerUpdateCycle){
            //runLogick();
            //  putchar('l');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }
        runInput();
        glfwPollEvents();

        runRender();
        usleep( (current+clocksPerFrame-clock()) > 0 ? (current+clocksPerFrame-clock()) : 0);
        i++;

        if(glfwGetKey(graph.window, GLFW_KEY_ESCAPE ) == GLFW_PRESS &&
           glfwWindowShouldClose(graph.window) != 0 )
            game.isRunning = GL_FALSE;

    }
}


void Game::runRender() {
    //  putchar('r');

    __glewClearBufferfv(GL_COLOR, 0, graph.winProperties.backColor);
    __glewClearBufferfv(GL_DEPTH, 0, nullptr);

    graph.winProperties.backColor[0] = 0.2;
    graph.winProperties.backColor[1] = 0.1;
    graph.winProperties.backColor[2] = (float)sin(((double)clock()/10) / 100000);
    printf("%lf %lf\n",
            gameInstance->game.player.horizontalAngle,
           gameInstance->game.player.verticalAngle);


    /*
    //  todo debug
    printf("\nMatrix:\n");
    for(uint i=0 ; i<16 ; i++)
        printf("%f %c", graph.winProperties.view.v[i], (i+1)%4 ? ' ' : '\n');
        */


    /*
     ourShader.use();
     ourShader.setMat4("projection", projection);
     ourShader.setMat4("view", view);


     glm::mat4 model = glm::mat4(1.f);

     ourShader.setMat4("model", model);
     ourModel.Draw(ourShader);


     */


    glUseProgram(graph.winProperties.program);

    glUniformMatrix4fv(graph.matrixID, 1, GL_FALSE, (float*)&graph.winProperties.view);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graph.texture);
    glUniform1i(graph.textureID, 0);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, graph.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, graph.uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)game.triaBuffer->len * 4);
    //  for()
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


    glfwSwapBuffers(graph.window);
    glfwPollEvents();

}


void Game::runInput() {
    //consts
    // todo: turn everything into radians
    float mouseSens = 0.005f;
    //  static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - game.gameProps.lastCycleTime);

    //  MOUSE INPUT
    double xPos, yPos;
    glfwGetCursorPos(graph.window, &xPos, &yPos);
    glfwSetCursorPos(graph.window, (float)graph.winProperties.size.x/2.0f, (float)graph.winProperties.size.y/2.0f);

    //  player view angles
    game.player.horizontalAngle += mouseSens * deltaTime * (float)(graph.winProperties.size.x/2.0f - xPos);
    game.player.verticalAngle += mouseSens * deltaTime * (float)(graph.winProperties.size.y/2.0f - yPos);

    glm::vec3 direction = glm::vec3(
            cosf(game.player.verticalAngle) * sinf(game.player.horizontalAngle),
            sinf(game.player.verticalAngle),
            cosf(game.player.verticalAngle) * cosf(game.player.horizontalAngle)
    );

    game.player.view = direction;


/*
    game.player.view.x = cosf(game.player.verticalAngle) * sinf(game.player.horizontalAngle) + game.player.getPos().x;
    game.player.view.y = sinf(game.player.verticalAngle) + game.player.getPos().y;
    game.player.view.z = cosf(game.player.horizontalAngle) * cosf(game.player.verticalAngle) + game.player.getPos().z;
*/

    glm::vec3 right = glm::vec3(
            sinf(game.player.horizontalAngle - (float)M_PI / 2.0f),
            0.0f,
            cosf(game.player.horizontalAngle - (float)M_PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);


    {//  read KEYBOARD INPUT
        if (glfwGetKey(graph.window, GLFW_KEY_W) == GLFW_PRESS)
            game.player.addPosition(direction * deltaTime * game.player.movementSpeedMultiplier);
        if (glfwGetKey(graph.window, GLFW_KEY_S) == GLFW_PRESS)
            game.player.addPosition(-1.f * direction * deltaTime * game.player.movementSpeedMultiplier);
        if (glfwGetKey(graph.window, GLFW_KEY_D) == GLFW_PRESS)
            game.player.addPosition(right *  deltaTime * game.player.movementSpeedMultiplier);
        if (glfwGetKey(graph.window, GLFW_KEY_A) == GLFW_PRESS)
            game.player.addPosition( -1.f * right * deltaTime * game.player.movementSpeedMultiplier);
        if (glfwGetKey(graph.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            game.isRunning = GL_FALSE;
    }

    glm::mat4 model(1.f);

    glm::mat4 projection = glm::perspective(glm::radians(game.player.initialFOV), 1280.0f / 800.0f, 0.01f, 10245.0f);

    glm::mat4 viewMatrix = glm::lookAt(game.player.getPos(), game.player.getPos() + direction, up);

    graph.winProperties.view = projection * viewMatrix * model;

    /*
    Matrics4f projection;

    getPerspectiveMatrix_Wrapper(projection.v, game.player.initialFOV, (float)graph.winProperties.size.x / graph.winProperties.size.y, 0.01f, 10245.f);
    getViewMatrix_Wrapper(&graph.winProperties.view.v[0], game.player.getPos(), game.player.view, up, &projection.v[0]);
     */


    game.gameProps.lastCycleTime = currentTime;

}


Game::~Game(){
    glDeleteBuffers(1, &graph.vertexBuffer);
    glDeleteProgram(graph.winProperties.program);
    glDeleteTextures(1, &graph.texture);
    for(int i=0 ; i<graph.takenVertexNumber ; ++i)
        glDeleteVertexArrays(1, &graph.VertexArrayIDs[i]);

    //  glfwTerminate();

}

//  misc
GLboolean* Game::getRunFlagPtr() {
    if(gameInstance == nullptr) {
        //  _exit(134);
        //  return ptr on TRUE to work while game is being intialized
        return &Game::truePtr;
    }

    return &gameInstance->game.isRunning;
}


//  todo remove
void Game::fillPolys(float* polys){
    polys[0] = 0.0f, polys[1] = 0.0f, polys[2] = 0.0f;       // a
    polys[3] = 4000.0f, polys[4] = 4000.0f, polys[5] = 4000.0f;
    polys[6] = 0.0f, polys[7] = 40.0f, polys[8] = 0.0f;
    //
    polys[9] = 40.0f, polys[10] = 40.0f, polys[11] = 40.0f;
    polys[12] = 40.0f, polys[13] = 80.0f, polys[14] = 40.0f;
    polys[15] = 40.0f, polys[16] = 40.0f, polys[17] = 400.0f;

}


//  static singleton
Game* Game::getGame() {
    if(gameInstance == nullptr) {
        gameInstance = new Game();
    }

    return gameInstance;
}
