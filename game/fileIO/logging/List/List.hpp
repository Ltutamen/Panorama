//
// Created by axiom on 6/15/19.
//

#ifndef PANORAMA_LIST_HPP
#define PANORAMA_LIST_HPP

#include "../../../mathematics/vectors/Vectors.hpp"

typedef struct ListNode{
    char* val;
    struct ListNode* next;
}ListNode;

typedef struct{
    ListNode* head;
    uint size;
}List;

List* newList();
void listPush(List* list, char* val);
char* listPop(List* list);
void listDestro(List* list);

#endif //PANORAMA_LIST_HPP
