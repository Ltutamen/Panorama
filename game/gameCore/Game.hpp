//
// Created by axiom on 6/11/19.
//

#ifndef PANORAMA_GAME_HPP
#define PANORAMA_GAME_HPP


#include "../../graphics/window/Window.hpp"
#include "../fileIO/logging/Logger.hpp"
#include "World/World.h"
#include "GGraph.h"
#include "../gameWorld/movingThings/player/Player.hpp"
#include "../gameProperties/GameProperties.hpp"

#include <GLFW/glfw3.h>


//  todo refactor
class GGame {
public:
    GGame();

    GLboolean isRunning;
    Player player;
    GameProperties gameProps;
    Vectornf* triaBuffer;
    Logger* logger;

    //  new
    World world;
};



class Game{
public:
    //  returns ptr to the runFlag
    static GLboolean* getRunFlagPtr();
    static Game* getGame();

    //  graphical content of the game
    GGraph graph;

    GGame game;
    //  always points at some GLBoolean true value
    static GLboolean truePtr;

    //  runs game loop
    void run();

    ~Game();

    static const uint targetFPS = 100;
    static const uint targetUPS = 1;
    static const long clocksInSecond = 100;

private:

    Game();

    static Game* gameInstance;
    void gameOpenGlInit();

    //  todo remove
    void fillPolys(float* polys);

    void runRender();
    void initRender();
    void runInput();

};



#endif //PANORAMA_GAME_HPP
