//
// Created by axiom on 6/12/19.
//

#ifndef PANORAMA_LOGGER_HPP
#define PANORAMA_LOGGER_HPP

#include <bits/types/FILE.h>
#include <zconf.h>
#include "syncQueue/syncQueue.hpp"

/*
typedef struct{
    FILE* f;
    pthread_t loggerThread;
    void* runningFlag;
    SQueue* writingQueue;
}Logger;

//  logger destroys itself on game end  //  todo delete pointer
Logger* newLogger(const char* filepath, unsigned char* runningFlag);
void logToFile(Logger* logger, const char* messearge);
 */

class Logger {
public:
    static void log(const char* message);

private:
    typedef struct{
        FILE* f;
        pthread_t loggerThread;
        void* runningFlag;
        SQueue* writingQueue;
    } SLogger;

    static SLogger* _logger;

    static SLogger* newLogger(const char* filepath, unsigned char* runningFlag);
    static void logToFile(SLogger* logger, const char* messearge);
    static void destroyLogger(Logger::SLogger* logger);

    //  concurent part
    static void* runLogger(void* currentLogger);

};

#endif //PANORAMA_LOGGER_HPP
