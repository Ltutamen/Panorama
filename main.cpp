#include "game/gameCore/Game.hpp"
#include <cstdio>


int main() {
    Logger::log("game starts");
    Game* game = Game::getGame();
    game->run();

    delete game;

    printf("Hello, World!\n");
    return 0;
}
