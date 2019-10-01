//
// Created by axiom on 6/12/19.
//

#include <malloc.h>
#include <pthread.h>
#include <GL/gl.h>
#include "Logger.hpp"


//  Friend functions declaration
void logToFile(FILE* f, const char* msg);
void* run(void* logger);


Logger::Logger(const char *filePath, int *runningFlag) {
    this->file = fopen(filePath, "wt");
    this->runningFlag = runningFlag;
    this->writingQueue = new SyncQueue();
    pthread_create(&this->loggerThread, NULL, &run, this);
}

/*
Logger* newLogger(const char* filepath, unsigned char* runningFlag){
    Logger* result = (Logger*)malloc(sizeof(Logger));
    result->f = fopen(filepath, "wt");
    result->runningFlag = runningFlag;
    result->writingQueue = newSQueue();
    pthread_create(&result->loggerThread, NULL, &runLogger, result);

    return result;
} */


/*
//  simply adds to queue messearge
void logToFile(Logger* logger, const char* messearge){
    if(logger == NULL)
        _exit(133);

    putSQueue(logger->writingQueue, messearge);
} */

/**
 * Runs an infinite cycle, that logs messages from the queue into the file
 */
void* run(void* currentLogger){
    auto logger = (Logger*)currentLogger;

    logToFile(logger->file, "LOGGER MSG : logger started!\0");
    //  While global running variable is not null
    while((*(int*)logger->runningFlag) == GL_TRUE) {
       if(!logger->writingQueue->isEmpty())
           logToFile(logger->file, logger->writingQueue->pop());
    }

    logToFile(logger->file, "LOGGER MSG : logger ended!\0");

    //  while(!logger->writingQueue->isEmpty());

    //delete (Logger*)currentLogger;

    return nullptr;
}


/**
 * Writes @msg into file @f in a fansy way
 */
void logToFile(FILE* f, const char* msg) {
    time_t  now = time(nullptr);

    struct tm*  ctm = localtime(&now);
    fprintf(f, "[y:%i,m:%i,d:%i]:[%i:%i:%i]", ctm->tm_year + 1900, ctm->tm_mon, ctm->tm_mday,
            ctm->tm_hour, ctm->tm_min, ctm->tm_sec);

    fprintf(f, "{%s}\n", msg);
    //  free((void*)msg);
}

/**
 * Adds @messeage into end of the logger queue
 */
void Logger::log(const char *messeage) {
    writingQueue->put(messeage);
}

Logger::~Logger() {
    fclose(file);
    //  queue is already free
    delete writingQueue;
}