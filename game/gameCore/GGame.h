//
// Created by myself on 1/16/20.
//

#ifndef PANORAMA_GGAME_H
#define PANORAMA_GGAME_H


#include <GL/glew.h>
#include "../player/Player.hpp"
#include "../gameProperties/GameProperties.hpp"
#include "World/World.h"

class GGame {
public:

    GGame();
    GLboolean isRunning;
    Player player;
    GameProperties gameProps;
    Vectornf* triaBuffer;

    //  new
    World world;
};


#endif //PANORAMA_GGAME_H
