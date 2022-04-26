#ifndef UNTITLED_LINKED_LIST_H
#define UNTITLED_LINKED_LIST_H

#include "Defs.h"
//Defs
typedef void* Element;
typedef struct Node_t* Node;
typedef struct Linked_List_t* Linked_List;

//fuctions' pointers
typedef element (*CopyFun)(Element);
typedef status (*FreeFun)(Element);
typedef int (*CompareFun)(Element,Element);
typedef status (*PrintFun)(Element);
typedef char* (*GetCategory)(Element);

//Node
Element get_Element(Node node);
Node get_Next_Node(Node node);
Node get_First_Node(Linked_List list);
Node get_Last_Node(Linked_List list);
int get_List_Size(Linked_List list);

//Linked List
Linked_List createLinkedList(FreeFun freeElement, CopyFun CopyElement, CompareFun compareElement, PrintFun printElement,GetCategory getCategory);
Node searchByKeyInList(Linked_List list, Element element);
status deleteNode(Linked_List list, Element element);
status appendNode(Linked_List list, Element element);
void displayList(Linked_List list);
void destroyList(Linked_List list);

#endif //UNTITLED_LINKED_LIST_H
