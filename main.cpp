#include "game/gameCore/Game.hpp"
#include "game/fileIO/fastConfig/FastConfig.h"
#include <cstdio>

void fillPolys(float*);
void fastConfTest();

int main() {
    Game* game = Game::getGame();
    gameLoop(game);

    printf("Hello, World!\n");
    return 0;
}



void fastConfTest(){
    FastConfig* config = new FastConfig("resources/fconfigs/test.fconf");
    printf("%f", (float)config->getVal(1));
    printf("%i", (int)config->getVal(2));
    getchar();
}