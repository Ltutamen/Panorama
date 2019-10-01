//
// Created by axiom on 6/15/19.
//

#include <malloc.h>
#include <stdlib.h>
#include "List.hpp"

List* newList(){
    List* result = (List*)malloc(sizeof(List));
    result->size = 0;
    result->head = NULL;
    return result;
}


void listPush(List* list, char* val){
    if(list == NULL || val == NULL)
        exit(55);

    ListNode* curr = list->head;
    if(curr = NULL){
        list->head = (ListNode*)malloc(sizeof(ListNode));
        list->head->next = NULL;
        for(int i=0 ; val[i]!='\0' ; ++i)
            list->head->val[i] = val[i];

    }
    else{
        while(curr->next!=NULL)
            curr = curr->next;

        curr->next = (ListNode*)malloc(sizeof(ListNode));
        curr->next = NULL;
        for(int i=0 ; val[i]!='\0' ; ++i)
            curr->next->val[i] = val[i];
    }
    list->size++;
    return;

}


char* listPop(List* list){
    if(list == NULL)
        exit(55);

    if(list->size == 0 || list->head == NULL)
        return NULL;

    ListNode* temp = list->head->next;
    char* text = temp->val;
    free(list->head);
    list->head = temp;
    return text;

}


void listDestroy(List* list){
    if(list == NULL)
        return;

    ListNode* temp;
    for(ListNode* curr = list->head ; curr!=NULL ; curr =curr->next){
        temp = curr->next;
        free(curr);
        curr = temp;
    }

    free(list);
}
