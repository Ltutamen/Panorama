//
// Created by axiom on 8/22/19.
//

#include "FastConfig.h"

/*
private:
    const char* filepath;
    FILE* file;
*/

FastConfig::FastConfig(const char* filepath){
    this->filepath = filepath;
    this->file = fopen(filepath, "r");
    fscanf(this->file, "%u", &this->offset);
}


FastConfig::~FastConfig() {
    fclose(file);
    // filepath is not our business
}


int32 FastConfig::getVal(uint32 pos){
    fseek(file, offset + 4*(--pos), SEEK_SET);
    int result;
    fscanf(file, "%i", &result);
    return result;

}

