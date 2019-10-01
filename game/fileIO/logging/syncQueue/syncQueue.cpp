//
// Created by axiom on 6/19/19.
//

#include <memory.h>
#include "syncQueue.hpp"

/*
SQueue* newSQueue(){
    SQueue* result = (SQueue*)malloc(sizeof(SQueue));
    sem_init(&result->qSem, 0, 0);
    sem_post(&result->qSem);
    result->head = NULL;
    return result;
}
*/
/*
int isNEmptyQueue(SQueue* queue){
    return queue->head != NULL;
}
*/
/*
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
*/
SyncQueue::SyncQueue() {
    sem_init(&this->sem, 0, 0);
    sem_post(&this->sem);
    this->head = nullptr;
}

/**
 * Puts @string as a first element in the queue
 *
 */
void SyncQueue::put(const char* string) {
    auto* add = new QNode(string);
    sem_wait(&sem);

    if(head == nullptr)
        this->head = add;
    else {
        add->next = this->head;
        this->head = add;
    }

    sem_post(&this->sem);

}


const char* SyncQueue::pop() {
    if(head == nullptr)
        _exit(3);

    const char *result;

    sem_wait(&sem);
    {
        QNode *curr = head;
        QNode *prev = nullptr;

        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }

        result = curr->val;

        if (prev != nullptr) {
            delete prev->next;
            prev->next = nullptr;
        } else {
            delete head;
            head = nullptr;
        }
    }
    sem_post(&sem);

    return result;
}


SyncQueue::QNode::QNode(const char *string) {
    this->next = nullptr;
    this->val = string;
}


bool SyncQueue::isEmpty() {
    return this->head == nullptr;
}

/*
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
*/
/*
QNode* newQnode(const char* string){
    QNode* node = (QNode*)malloc(sizeof(QNode));
    node->next = NULL;
    node->val = (char*)malloc(sizeof(char) * strlen(string) + sizeof(char));
    for(size_t i=0 ; string[i]!='\0' ; ++i)
        node->val[i] = string[i];
    return node;
}
*/



SyncQueue::QNode::~QNode() {
    //  value is beeing deleted in the logToFile func
    //  delete val;
}


SyncQueue::~SyncQueue() {
    //  while (!isEmpty());

    /*
     * deque is already empty
    QNode* node = head;
    while (head!= nullptr) {
        QNode* temp = node->next;
        delete node;
        node = temp;
    }
    */
}
