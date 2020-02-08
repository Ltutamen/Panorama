#include "game/gameCore/Game.hpp"

#include "assimp/Importer.hpp"


int main() {
    Logger::log(std::string("game starts"));
    Game* game = Game::getGame();
    game->run();

    delete game;
    return 0;
}

