//
// Created by axiom on 8/22/19.
//

#ifndef PANORAMA_FASTCONFIG_H
#define PANORAMA_FASTCONFIG_H


#include <cstdio>
#include "../../mathematics/vectors/Vectors.hpp"

class FastConfig {
private:
    const char* filepath;
    FILE* file;
    int offset;

public:
    FastConfig(const char* filepath);
    ~FastConfig();
    int getVal(uint32 pos);
};


#endif //PANORAMA_FASTCONFIG_H
