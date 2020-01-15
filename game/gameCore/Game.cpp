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

Game* Game::gameInstance = (Game*)(nullptr);
GLboolean Game::truePtr = GL_TRUE;

void runRender(Game* game);
void runInput(Game* game);
void destroyGame(Game* game);
void initRender(Game* game);

const uint targetFPS = 100;
const uint targetUPS = 1;
long clocksInSecond = 100;

long clocksPerFrame;
long clocksPerUpdate;



static void gameOpenGlInit(Game* game);
GGame nGGame();
GGraph nGGraph();

Game* newGame(Vectornf* polys){
    Game *game = (Game*)malloc(sizeof(Game));

    game->game = nGGame();
    game->game.triaBuffer = polys;

    game->graph.VertexArrayIDs = (GLuint*)malloc(sizeof(GLuint) * 50);

    Game::gameOpenGlInit(game);

    //uv buffer filling // todo autogen
    game->graph.uvBuffer = (GLfloat*)malloc(sizeof(GLfloat) * 2 * 6);
    game->graph.uvBuffer[0] = 0.01f; game->graph.uvBuffer[1] = 0.01f;
    game->graph.uvBuffer[2] = 0.01f; game->graph.uvBuffer[3] = 0.01f;
    game->graph.uvBuffer[4] = 0.01f; game->graph.uvBuffer[5] = 0.01f;

    game->graph.uvBuffer[6] = 0.99f; game->graph.uvBuffer[7] = 0.99f;
    game->graph.uvBuffer[8] = 0.99f; game->graph.uvBuffer[8] = 0.01f;
    game->graph.uvBuffer[10] = 0.99f; game->graph.uvBuffer[11] = 0.01f;
    glGenBuffers(1, &game->graph.uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, game->graph.uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(game->graph.uvBuffer), game->graph.uvBuffer, GL_STATIC_DRAW);

    return game;

}


GGame nGGame(){
    GGame result;

    result.isRunning = GL_TRUE;
    result.gameProps.lastCycleTime = glfwGetTime();
    result.player = nPlayer();
    //  result.logger = newLogger("currentLog.txt", &result.isRunning);

    //  new
//      result.world.addMesh(new Mesh(SKYBLOCK_SPHERE));

    return result;
}


void Game::gameOpenGlInit(Game* game) {
    if (!glfwInit())
        exit(2);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);

    game->graph.winProperties.size.x = 1280;
    game->graph.winProperties.size.y = 800;
    game->graph.window = glfwCreateWindow(game->graph.winProperties.size.x, game->graph.winProperties.size.y, "Faust\0", NULL, NULL);

    if(!game->graph.window) {
        Logger::log("ERROR at glfwCreateWindow(...), window failed to create\0");
        exit(1);
    }

    glfwShowWindow(game->graph.window);
    glfwMakeContextCurrent(game->graph.window);

    Logger::log("OpenGL Version: \0");
    Logger::log((char*)glGetString(GL_VERSION));
    Logger::log((char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

    if(glewInit() != GLEW_OK) {
        Logger::log("ERROR: glewInit() is not GLEW_OK in gameOpenGlinit()");
        exit(1);
    }

    glfwSetInputMode(game->graph.window, GLFW_STICKY_KEYS, GL_TRUE);

    //VAO initialization
    glGenVertexArrays(1, &(game->graph.VertexArrayIDs[0]));
    glBindVertexArray(game->graph.VertexArrayIDs[0]);

    //Buffer Creation
    glGenBuffers(1, &game->graph.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, game->graph.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * game->game.triaBuffer->len, game->game.triaBuffer->arr, GL_STATIC_DRAW);

    game->graph.winProperties = newWindowProperties();
    game->game.player = *newPlayer();
    game->graph.matrixID = glGetUniformLocation(game->graph.winProperties.program, "MWP");

    glfwSetInputMode(game->graph.window, GLFW_STICKY_KEYS, GL_TRUE);

    game->graph.texture = loadBMP("../resources/text1.bmp");
    game->graph.textureID = glGetUniformLocation(game->graph.winProperties.program, "exampleTexture");
}


void gameLoop(Game* game){
    initRender(game);

    clocksPerFrame = CLOCKS_PER_SEC/targetFPS;
    clocksPerUpdate = CLOCKS_PER_SEC/targetUPS;
    long clocksPerUpdateCycle = 0;

    printf("\n Clocks per sec %d", (int)CLOCKS_PER_SEC);

    long previous = clock() - clocksPerFrame;
    int i = 0;
    long lag = 0;

    while(game->game.isRunning == GL_TRUE){

        //  printf("\nLoop%i ", i);

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
        runInput(game);
        glfwPollEvents();

        runRender(game);
        usleep( (current+clocksPerFrame-clock()) > 0 ? (current+clocksPerFrame-clock()) : 0);
        i++;

        if(glfwGetKey(game->graph.window, GLFW_KEY_ESCAPE ) == GLFW_PRESS &&
           glfwWindowShouldClose(game->graph.window) != 0 )
            game->game.isRunning = GL_FALSE;

    }

    destroyGame(game);

}


void initRender(Game* game){
    Matrics4f model = Matrics4fVal(1.0f);
    matrics4fMult(&game->graph.winProperties.view, &model);
    matrics4fMult(&game->graph.winProperties.projection, &game->graph.winProperties.view);
    game->graph.matrixID = glGetUniformLocation(game->graph.winProperties.program, "MVP");

}


void runRender(Game* game){
    //  putchar('r');

    __glewClearBufferfv(GL_COLOR, 0, game->graph.winProperties.backColor);

    game->graph.winProperties.backColor[0] = 0.2;
    game->graph.winProperties.backColor[1] = 0.1;
    game->graph.winProperties.backColor[2] = (float)sin(((double)clock()/10) / 100000);


    /*
    //  todo debug
    printf("\nMatrix:\n");
    for(uint i=0 ; i<16 ; i++)
        printf("%f %c", game->graph.winProperties.view.v[i], (i+1)%4 ? ' ' : '\n');
        */


    glUseProgram(game->graph.winProperties.program);

    glUniformMatrix4fv(game->graph.matrixID, 1, GL_FALSE, (float*)&game->graph.winProperties.view.v);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, game->graph.texture);
    glUniform1i(game->graph.textureID, 0);


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, game->graph.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, game->graph.uvbuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)game->game.triaBuffer->len * 4);
    //  for()
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glfwSwapBuffers(game->graph.window);
    glfwPollEvents();

}


void destroyGame(Game* game){
    glDeleteBuffers(1, &game->graph.vertexBuffer);
    glDeleteProgram(game->graph.winProperties.program);
    glDeleteTextures(1, &game->graph.texture);
    for(int i=0 ; i<game->graph.takenVertexNumber ; ++i)
        glDeleteVertexArrays(1, &game->graph.VertexArrayIDs[i]);

    //  glfwTerminate();

}


void GGraph::addMesh(Mesh *mesh) {


}


GLboolean* Game::getRunFlagPtr() {
    if(gameInstance == nullptr) {
        //  _exit(134);
        //  return ptr on TRUE to work while game is being intialized
        return &Game::truePtr;
    }

    return &gameInstance->game.isRunning;
}


//  todo remove
void fillPolys(float* polys){
    polys[0] = 0.0f, polys[1] = 0.0f, polys[2] = 0.0f;       // a
    polys[3] = 4000.0f, polys[4] = 4000.0f, polys[5] = 4000.0f;
    polys[6] = 0.0f, polys[7] = 40.0f, polys[8] = 0.0f;
    //
    polys[9] = 40.0f, polys[10] = 40.0f, polys[11] = 40.0f;
    polys[12] = 40.0f, polys[13] = 80.0f, polys[14] = 40.0f;
    polys[15] = 40.0f, polys[16] = 40.0f, polys[17] = 400.0f;

}


Game::Game() {
    Vectornf* polys = newVectornf(6 * 3);
    fillPolys(polys->arr);
    game = nGGame();
    game.triaBuffer = polys;

    graph.VertexArrayIDs = (GLuint*)malloc(sizeof(GLuint) * 50);

    gameOpenGlInit(this);

    //uv buffer filling // todo autogen
    graph.uvBuffer = (GLfloat*)malloc(sizeof(GLfloat) * 2 * 6);
    graph.uvBuffer[0] = 0.01f; graph.uvBuffer[1] = 0.01f;
    graph.uvBuffer[2] = 0.01f; graph.uvBuffer[3] = 0.01f;
    graph.uvBuffer[4] = 0.01f; graph.uvBuffer[5] = 0.01f;

    graph.uvBuffer[6] = 0.99f; graph.uvBuffer[7] = 0.99f;
    graph.uvBuffer[8] = 0.99f; graph.uvBuffer[8] = 0.01f;
    graph.uvBuffer[10] = 0.99f; graph.uvBuffer[11] = 0.01f;
    glGenBuffers(1, &graph.uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, graph.uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(graph.uvBuffer), graph.uvBuffer, GL_STATIC_DRAW);

}


Game* Game::getGame() {
    if(gameInstance == nullptr) {
        gameInstance = new Game();
    }

    return gameInstance;
}
