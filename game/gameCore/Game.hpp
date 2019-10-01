//
// Created by axiom on 6/11/19.
//

#ifndef PANORAMA_GAME_HPP
#define PANORAMA_GAME_HPP


#include "../player/Player.hpp"
#include "../gameProperties/GameProperties.hpp"
#include "../../graphics/window/Window.hpp"
#include "../fileIO/logging/Logger.hpp"
#include "../../thirdParties/glm/glm/glm.hpp"
#include <GLFW/glfw3.h>

/**
 * Graphical part of tha game
 */
class GGraph{
public:
    GGraph(Logger* mainLogger);
    ~GGraph();

    GLFWwindow* window;
    WindowProperties* winProperties;
    //  todo move app into
    GLint matrixID;
    glm::mat4 mvp;

    //  textures and uv arr
    GLuint texture;
    GLuint textureID;
    GLfloat* uvBuffer;
    GLuint uvBufferID;

    //  vertex arr
    GLuint vertexArrayID;
    GLuint vertexBuffer;

    //  shader
    GLuint program;

    void openGLInit(Logger* mainLgger);
};

/**
 * Backend part of the game
 */
class GGame{
public:
    Player player;
    GameProperties gameProps;
    Logger* logger;

    // todo delete
    Vectornf* triaBuffer{};

    GGame();
    ~GGame();

private:

};

//  todo move shader init from winProperties



class Game {
public:
    GGraph graph;
    GGame game;

    //  Pointer to a global running flag var from main.c
    GLboolean* isRunning;

    Logger* mainLogger;

    Game(Vectornf* polys, GLboolean* globalRunFlag, Logger* logger);
    ~Game();

    //  runs initialization
    void run();

private:
    void init(Vectornf* init);
    //  void openGlInit();
    void shadersInit();

    //  Initializes things, that are being tested, should not appear in release
    void testInit(Vectornf* polys);

    //  call this when wanna play
    void gameLoop();
    void runInput();
    void runRender();
    void destroyGame();
};




Game* newGame(Vectornf* polys);
void gameLoop(Game* game);


#endif //PANORAMA_GAME_HPP
