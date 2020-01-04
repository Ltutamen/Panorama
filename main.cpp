#include "game/gameCore/Game.hpp"
#include "game/fileIO/fastConfig/FastConfig.h"
#include <cstdio>

void fillPolys(float*);
void fastConfTest();

int main() {
    //  matrTest();
    //  getchar();
    //  fastConfTest();
    Vectornf* polys = newVectornf(6 * 3);
    fillPolys(polys->arr);


    Game* game = newGame(polys);
    gameLoop(game);

    printf("Hello, World!\n");
    return 0;
}


void fillPolys(float* polys){
    polys[0] = 0.0f, polys[1] = 0.0f, polys[2] = 0.0f;       // a
    polys[3] = 4000.0f, polys[4] = 4000.0f, polys[5] = 4000.0f;
    polys[6] = 0.0f, polys[7] = 40.0f, polys[8] = 0.0f;
    //
    polys[9] = 40.0f, polys[10] = 40.0f, polys[11] = 40.0f;
    polys[12] = 40.0f, polys[13] = 80.0f, polys[14] = 40.0f;
    polys[15] = 40.0f, polys[16] = 40.0f, polys[17] = 400.0f;

}


void fastConfTest(){
    FastConfig* config = new FastConfig("resources/fconfigs/test.fconf");
    printf("%f", (float)config->getVal(1));
    printf("%i", (int)config->getVal(2));
    getchar();
}