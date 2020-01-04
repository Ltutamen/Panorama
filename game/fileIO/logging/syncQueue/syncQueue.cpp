//
// Created by axiom on 6/19/19.
//

#include <memory.h>
#include "syncQueue.hpp"

SQueue* newSQueue(){
    SQueue* result = (SQueue*)malloc(sizeof(SQueue));
    sem_init(&result->qSem, 0, 0);
    sem_post(&result->qSem);
    result->head = NULL;
    return result;
}


void destroySQueue(SQueue* queue){
    if(queue == NULL)
        return;

    QNode* curr = queue->head;
    while (curr->next!=NULL){
        QNode* temp = curr->next;
        free(curr);
        curr = temp;
    }
    free(queue);
}


int isNEmptyQueue(SQueue* queue){
    return queue->head != NULL;
}


void putSQueue(SQueue* queue, const char* string){
    sem_wait(&queue->qSem);

    if(queue->head == NULL)
        queue->head = newQnode(string);
    else{
        QNode* add = newQnode(string);
        add->next = queue->head;
        queue->head = add;
    }

    sem_post(&queue->qSem);
}


char* popSQueue(SQueue* queue){
    if(queue == NULL || queue->head == NULL)
        _exit(133);

    sem_wait(&queue->qSem);

    QNode* curr = queue->head;
    QNode* prev = NULL;
    while(curr->next!=NULL){
        prev = curr;
        curr = curr->next;
    }
    char* result = curr->val;
    if(prev != NULL) {
        free(prev->next);
        prev->next = NULL;
    }
    else{
        free(queue->head);
        queue->head = NULL;
    }

    sem_post(&queue->qSem);

    return result;
}


QNode* newQnode(const char* string){
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->next = NULL;
    node->val = (char*)malloc(sizeof(char) * strlen(string) + sizeof(char));
    for(size_t i=0 ; string[i]!='\0' ; ++i)
        node->val[i] = string[i];
    return node;
}