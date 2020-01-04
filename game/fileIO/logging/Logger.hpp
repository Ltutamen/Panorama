//
// Created by axiom on 6/12/19.
//

#ifndef PANORAMA_LOGGER_HPP
#define PANORAMA_LOGGER_HPP

#include <bits/types/FILE.h>
#include <zconf.h>
#include "syncQueue/syncQueue.hpp"


typedef struct{
    FILE* f;
    pthread_t loggerThread;
    void* runningFlag;
    SQueue* writingQueue;
}Logger;

//  logger destroys itself on game end  //  todo delete pointer
Logger* newLogger(const char* filepath, unsigned char* runningFlag);
void logToFile(Logger* logger, const char* messearge);

#endif //PANORAMA_LOGGER_HPP
