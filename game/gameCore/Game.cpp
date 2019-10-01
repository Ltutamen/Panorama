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

#include "../../graphics/window/Window.hpp"
#include "../../graphics/textures/Texture.hpp"
#include "../../thirdParties/glm/glm/gtc/matrix_transform.hpp"
#include "../../graphics/shaders/Shader.hpp"

constexpr uint targetFPS = 10;
constexpr uint targetUPS = 1;
long clocksInSecond = 100;

long clocksPerFrame;
long clocksPerUpdate;


Game::~Game() {
    printf("Game destructor\n");
    //  game already destroyed
    //  logger already destroyed
}

GGraph::~GGraph() {

}


//  djn 'nj j[etnm? cgbcrb bybwbfkbpfwbb njg
Game::Game(Vectornf* polys, GLboolean* globalRunFlag, Logger* logger) : graph(logger) {
    printf("Game constructor");
    //  GGraph and GGame constructors are auto called
    this->isRunning = globalRunFlag;
    this->mainLogger = logger;

    //  todo test
    this->game.triaBuffer = polys;

    init(polys);

}


void Game::init(Vectornf* polys) {
    testInit(polys);
    shadersInit();
}


void Game::run() {
    mainLogger->log("mainLoop() start");
    gameLoop();
}


void Game::testInit(Vectornf* polys) {
    //uv buffer filling
    graph.uvBuffer = (GLfloat*)malloc(sizeof(GLfloat) * 2 * 6);
    graph.uvBuffer[0] = 0.01f; graph.uvBuffer[1] = 0.01f;
    graph.uvBuffer[2] = 0.01f; graph.uvBuffer[3] = 0.01f;
    graph.uvBuffer[4] = 0.01f; graph.uvBuffer[5] = 0.01f;

    graph.uvBuffer[6] = 0.99f; graph.uvBuffer[7] = 0.99f;
    graph.uvBuffer[8] = 0.99f; graph.uvBuffer[8] = 0.01f;
    graph.uvBuffer[10] = 0.99f; graph.uvBuffer[11] = 0.01f;

    //  UV buffer
    glGenBuffers(1, &graph.uvBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, graph.uvBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(graph.uvBuffer), graph.uvBuffer, GL_STATIC_DRAW);

    //VAO initialization
    glGenVertexArrays(1, &(graph.vertexArrayID));
    glBindVertexArray(graph.vertexArrayID);

    //Buffer Creation
    glGenBuffers(1, &graph.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, graph.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * polys->len, polys->arr, GL_STATIC_DRAW);

    //  texture testing
    graph.texture = loadBMP("../resources/text1.bmp");
    graph.textureID = glGetUniformLocation(graph.program, "exampleTexture");
}


GGame::GGame(){
    //  todo player and things
    gameProps.lastCycleTime = glfwGetTime();
}


GGame::~GGame() {

}


GGraph::GGraph(Logger* mainLgger) {
    //  todo remove shaders from the win properties
    this->winProperties = newWindowProperties();
    openGLInit(mainLgger);

    char fragment[] = "../graphics/shaders/fragment001.fs\0";
    char vertex[] = "../graphics/shaders/vertex001.vs\0";
    program = makeShaderProgram(fragment, vertex);
    this->mvp = glm::mat4(1.f);
    //  mvp
}


void GGraph::openGLInit(Logger* mainLogger){
    if (!glfwInit()) {
        mainLogger->log("ERROR at <openGLInit>, glfwInit is null");
        exit(2);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    //  todo read from the config
    winProperties->size.x = 1280;
    winProperties->size.y = 800;
    window = glfwCreateWindow(winProperties->size.x, winProperties->size.y, "Faust\0", NULL, NULL);

    if(!window) {
        mainLogger->log( "ERROR at glfwCreateWindow(...), window failed to create\0");
        exit(2);
    }

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    mainLogger->log("OpenGL Version: \0");
    mainLogger->log((char*)glGetString(GL_VERSION));
    mainLogger->log((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    if(glewInit() != GLEW_OK) {
        mainLogger->log("ERROR: glewInit() is not GLEW_OK in gameOpenGlInit()");
        exit(2);
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //  todo all classes
    winProperties = newWindowProperties();

    matrixID = glGetUniformLocation(program, "MWP");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

}


void Game::gameLoop() {
    clocksPerFrame = CLOCKS_PER_SEC / targetFPS;
    clocksPerUpdate = CLOCKS_PER_SEC / targetUPS;
    long clocksPerUpdateCycle = 0;

    //  printf("\n Clocks per sec %d", (int)CLOCKS_PER_SEC);

    long previous = clock() - clocksPerFrame;
    int i = 0;
    long lag = 0;

    while(*isRunning == GL_TRUE){

        printf("\nLoop %i ", i);

        long current = clock();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        for(uint j = 0 ; lag>=clocksPerUpdateCycle && j<targetUPS ; j++) {
            //runLogick();
            putchar('u');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }

        while(lag >= clocksPerUpdateCycle){
            //runLogick();
            putchar('l');
            lag -= clocksPerUpdateCycle;
            clocksPerUpdateCycle = clock()- current;
        }

        runInput();
        glfwPollEvents();

        runRender();
        usleep( (current+clocksPerFrame-clock()) > 0 ? (current+clocksPerFrame-clock()) : 0);

        i++;

    }

    //  todo destructor
    destroyGame();

}


void Game::runInput() {
    // todo: turn everything into radians
    constexpr float mouseSens = 0.005f;
    static double lastTime;

    double currentTime = glfwGetTime();
    auto deltaTime = float(currentTime - lastTime);

    //  MOUSE INPUT
    double xPos, yPos;
    glfwGetCursorPos(graph.window, &xPos, &yPos);
    glfwSetCursorPos(graph.window, (float)graph.winProperties->size.x / 2.0f, graph.winProperties->size.y / 2.0f);

    //  player view angles
    game.player.horizAngl += mouseSens * deltaTime * (float)(graph.winProperties->size.x / 2.0f - xPos);
    game.player.vertAngl += mouseSens * deltaTime * (float)(graph.winProperties->size.y / 2.0f - yPos);

    glm::vec3 direction(
            cos(game.player.vertAngl) * sin(game.player.horizAngl),
            sin(game.player.vertAngl),
            cos(game.player.vertAngl) * cos(game.player.horizAngl)
    );

    glm::vec3 right = glm::vec3 (
            sinf(game.player.horizAngl - (float)M_PI / 2.0f),
            0.0f,
            cosf(game.player.horizAngl - (float)M_PI / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

   // game.player.view.x = cosf(game.player.vertAngl) * sinf(game.player.horizAngl) + game.player.pos.x;
   // game.player.view.y = sinf(game.player.vertAngl) + game.player.pos.y;
   // game.player.view.z = cosf(game.player.horizAngl) * cosf(game.player.vertAngl) + game.player.pos.z;



    {//  read KEYBOARD INPUT
        if (glfwGetKey(graph.window, GLFW_KEY_W) == GLFW_PRESS)
            game.player.pos += direction * deltaTime * game.player.mouseSpeed;
        if (glfwGetKey(graph.window, GLFW_KEY_S) == GLFW_PRESS)
            game.player.pos -= direction * deltaTime * game.player.mouseSpeed;
        if (glfwGetKey(graph.window, GLFW_KEY_A) == GLFW_PRESS)
            game.player.pos += right * deltaTime * game.player.mouseSpeed;
        if (glfwGetKey(graph.window, GLFW_KEY_D) == GLFW_PRESS)
            game.player.pos -= right * deltaTime * game.player.mouseSpeed;
        if (glfwGetKey(graph.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            *isRunning = GL_FALSE;
    }


    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)graph.winProperties->size.x / graph.winProperties->size.y, 0.1f, 4096.f);
    /*printf("\n PROJECTION\n");
    for(int i=0 ; i<4 ; ++i) {
        for (int j = 0; j < 4; ++j)
            printf("%lf ", projection[i][j]);
        putchar('\n');
    }
     */

    glm::mat4 view = glm::lookAt(game.player.camPos, game.player.camPos+direction, game.player.headsUp);
    /*printf("\n VIEW \n");
    for(int i=0 ; i<4 ; ++i) {
        for (int j = 0; j < 4; ++j)
            printf("%lf ", view[i][j]);
        putchar('\n');
    }
     */
    glm::mat4 model = glm::mat4(1.f);
    /*
    printf("\n MODEL\n");
    for(int i=0 ; i<4 ; ++i) {
        for (int j = 0; j < 4; ++j)
            printf("%lf ", model[i][j]);
        putchar('\n');
    }
     */

    graph.mvp = projection * view * model;
    /*
    printf("\n MVP:\n");
    for(int i=0 ; i<4 ; ++i) {
        for (int j = 0; j < 4; ++j)
            printf("%lf ", graph.mvp[i][j]);
        putchar('\n');
    }
     */

    lastTime = currentTime;
}


void Game::runRender(){
    putchar('r');

    //  __glewClearBufferfv(GL_COLOR, 0, graph.winProperties->backColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  graph.winProperties->backColor[0] = 0.2;
    //  graph.winProperties->backColor[1] = 0.1;
    //  graph.winProperties->backColor[2] = (float)sin(((double)clock()/10) / 100000);

    glUseProgram(graph.program);

    glUniformMatrix4fv(graph.matrixID, 1, GL_FALSE, &graph.mvp[0][0]);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graph.texture);
    glUniform1i(graph.textureID, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, graph.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, graph.uvBufferID);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)game.triaBuffer->len * 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(graph.window);
    glfwPollEvents();

}


void Game::destroyGame() {
    glDeleteBuffers(1, &graph.vertexBuffer);
    glDeleteProgram(graph.program);
    glDeleteTextures(1, &graph.texture);
    glDeleteVertexArrays(1, &graph.vertexArrayID);
    glfwTerminate();

}


void Game::shadersInit() {
    //  this->graph.winProperties = newWindowProperties();
}