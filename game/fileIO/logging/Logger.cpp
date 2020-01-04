//
// Created by axiom on 6/12/19.
//

#include <malloc.h>
#include <pthread.h>
#include <GL/gl.h>
#include "Logger.hpp"

void* runLogger( void* currentLogger );
void destroyLogger(Logger* logger);

Logger* newLogger(const char* filepath, unsigned char* runningFlag){
    Logger* result = (Logger*)malloc(sizeof(Logger));
    result->f = fopen(filepath, "wt");
    result->runningFlag = runningFlag;
    result->writingQueue = newSQueue();
    pthread_create(&result->loggerThread, NULL, &runLogger, result);

    return result;
}


//  simply adds to queue messearge
void logToFile(Logger* logger, const char* messearge){
    if(logger == NULL)
        _exit(133);

    putSQueue(logger->writingQueue, messearge);
}


void* runLogger( void* currentLogger){
    Logger* logger = (Logger*)currentLogger;

    logToFile(logger, "LOGGER MSG : logger started!\0");
    while(  logger->writingQueue->head!=NULL || *((unsigned char*)logger->runningFlag) == GL_TRUE ){
       if(isNEmptyQueue(logger->writingQueue)){
           time_t now = time(0);

           struct tm* ctm = localtime(&now);
           char* msg = popSQueue(logger->writingQueue);
           fprintf(logger->f, "[y:%i,m:%i,d:%i]:[%i:%i:%i]", ctm->tm_year + 1900, ctm->tm_mon, ctm->tm_mday,
                                                                ctm->tm_hour, ctm->tm_min, ctm->tm_sec);
           fprintf(logger->f, "{%s}\n", msg);

           free(msg);
       }
    }

    logToFile((Logger*)currentLogger, "LOGGER MSG : logger ended!\0");
    while(logger->writingQueue->head!=NULL);
    destroyLogger((Logger*)currentLogger);

    return NULL;
}


void destroyLogger(Logger* logger){
    if(logger == NULL)
        return;

    fclose(logger->f);
    free(logger->f);
    destroySQueue(logger->writingQueue);

}