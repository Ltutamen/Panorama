//
// Created by axiom on 6/12/19.
//

#include <malloc.h>
#include <pthread.h>
#include <GL/gl.h>
#include "Logger.hpp"
#include "../../gameCore/Game.hpp"


Logger::SLogger* Logger::_logger = (Logger::SLogger*)nullptr;


void Logger::log(const char* message) {
    if(_logger == nullptr)
        _logger = newLogger("default.log", Game::getRunFlagPtr());

    logToFile(_logger, message);

}


Logger::SLogger* Logger::newLogger(const char* filepath, unsigned char* runningFlag){
    SLogger* result = (SLogger*)malloc(sizeof(Logger));
    result->f = fopen(filepath, "wt");
    result->runningFlag = runningFlag;
    result->writingQueue = newSQueue();
    pthread_create(&result->loggerThread, NULL, &runLogger, result);

    return result;
}


//  simply adds to queue message
void Logger::logToFile(SLogger* logger, const char* message){
    if(logger == NULL)
        _exit(133);

    putSQueue(logger->writingQueue, message);
}


void* Logger::runLogger( void* currentLogger){
    SLogger* logger = (SLogger*)currentLogger;

    logToFile(logger, "<LOGGER MSG> : logger started!\0");
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

    logToFile((SLogger*)currentLogger, "LOGGER MSG : logger ended!\0");
    while(logger->writingQueue->head!=NULL);
    destroyLogger((SLogger*)currentLogger);

    return NULL;
}


void Logger::destroyLogger(Logger::SLogger* logger) {
    if(logger == NULL)
        return;

    fclose(_logger->f);
    //  free(_logger->f);
    destroySQueue(_logger->writingQueue);

}


void Logger::log(std::string message) {
    const char* cs_message = message.c_str();
    Logger::log(cs_message);

}
