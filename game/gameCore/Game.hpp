//
// Created by axiom on 6/11/19.
//

#ifndef PANORAMA_GAME_HPP
#define PANORAMA_GAME_HPP


#include "../player/Player.hpp"
#include "../gameProperties/GameProperties.hpp"
#include "../../graphics/window/Window.hpp"
#include "../fileIO/logging/Logger.hpp"
#include "World/World.h"
#include <GLFW/glfw3.h>


class GGraph {
public:
    GLFWwindow* window;
    WindowProperties winProperties;
    GLint matrixID;

    GLuint texture;
    GLint textureID;
    GLfloat* uvBuffer;
    GLuint uvbuffer;

    GLuint* VertexArrayIDs;
    int takenVertexNumber = 0;
    GLuint vertexBuffer;

    void addMesh(Mesh* mesh);
};


typedef struct {
    GLboolean isRunning;
    Player player;
    GameProperties gameProps;
    Vectornf* triaBuffer;
    Logger* logger;

    //  new
    World world;
}GGame;


class Game{
public:

    GGraph graph;
    GGame game;

    static GLboolean* getRunFlagPtr();
    static Game* getGame();

    static void gameOpenGlInit(Game* game);

    static GLboolean truePtr;

private:

    Game();
    static Game* gameInstance;




};


Game* newGame(Vectornf* polys);
void gameLoop(Game* game);


#endif //PANORAMA_GAME_HPP
