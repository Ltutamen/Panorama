#include "game/gameCore/Game.hpp"


int main() {
    Logger::log("game starts");
    Game* game = Game::getGame();
    game->run();

    delete game;
    return 0;
}
