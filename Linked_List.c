#include "Linked_List.h"
#include "Defs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node_t{
    Element NodeElement;
    Node Next;
    Node Prev;
};
struct Linked_List_t{
    Node First;
    Node Last;
    int List_Size;

    FreeFun freeElement;
    CopyFun CopyElement;
    CompareFun compareElement;
    PrintFun printElement;
    GetCategory getCategory;
};

Linked_List createLinkedList(FreeFun freeElement, CopyFun CopyElement, CompareFun compareElement, PrintFun printElement,GetCategory getCategory) {
    Linked_List arr = (Linked_List) malloc(sizeof(struct Linked_List_t));
    if (arr == NULL) {
        printf("No memory available\n");
        return NULL;
    }

    arr->First = NULL;
    arr->Last = NULL;
    arr->List_Size = 0;

    arr->freeElement=freeElement;
    arr->CopyElement=CopyElement;
    arr->compareElement=compareElement;
    arr->printElement=printElement;
    arr->getCategory=getCategory;
    return arr;
}

status appendNode(Linked_List list, Element element){
    if (list==NULL)
        return failure;
    if (list->List_Size==0){
    	Node node=(Node)malloc(sizeof(struct Node_t));
        if (node==NULL){
            printf("No memory available\n");
            return failure;
        }

        list->First=node;
        list->Last=node;
        node->NodeElement=element;
        node->Next=NULL;
        node->Prev=NULL;
        list->List_Size++;
        return success;
    }
    Node node=(Node)malloc(sizeof(struct Node_t));
    if (node==NULL) {
        printf("No memory available\n");
        return failure;
    }

    node->NodeElement=element;
    list->Last->Next=node;
    node->Prev=list->Last;
    list->Last=node;
    node->Next=NULL;
    list->List_Size++;
    return success;
}

Node searchByKeyInList(Linked_List list, Element element) {
    if (list == NULL)
        return NULL;
    if (list->List_Size == 0)
        return NULL;

    Node tmp = list->First;
    if (strcmp(list->getCategory(tmp->NodeElement), element)==0)
        return tmp;

    while (tmp->Next != NULL) {
        if (strcmp(list->getCategory(tmp->NodeElement), element)==0)
            return tmp;

        tmp = tmp->Next;
        if (tmp == list->Last) {
            if (strcmp(list->getCategory(tmp->NodeElement), element)==0)
                return tmp;
            else return NULL;
        }
    }
    return NULL;
}

status deleteNode(Linked_List list, Element element) {
    if (list == NULL)
        return failure;
    if (list->List_Size == 0)
        return failure;

    //search
    Node tmp=list->First;
    if (tmp->NodeElement != element) {
        while (tmp->Next != NULL) {
            if (tmp->NodeElement == element)
                break;
            if (tmp==list->Last){
                if (tmp->NodeElement == element)
                    break;
                else return failure;
            }
        }
    }

    if (list->List_Size==1){
    	list->freeElement(tmp->NodeElement);
		list->List_Size--;
		free(list->First);
		list->First = NULL;
		list->Last = NULL;
		return success;
    }
    if (tmp==list->Last) {
        tmp->Prev->Next=NULL;
        list->Last=list->Last->Prev;
    }
    else if (tmp==list->First){
        tmp->Next->Prev=NULL;
        list->First=tmp->Next;
    }
    else {
        tmp->Next->Prev = tmp->Prev;
        tmp->Prev->Next = tmp->Next;
    }
    list->freeElement(tmp->NodeElement);
    list->List_Size--;
    free(tmp);
    return success;
}

void destroyList(Linked_List list) {
    if(list == NULL)
    	return;
	if (list->First != NULL){
		Node current =list->First, next;
		while (current!=NULL) {
			next = current->Next;
			deleteNode(list, current->NodeElement);
			current = next;
		}
    }
    free(list);
}

Element get_Element(Node node){
    if (node==NULL)
        return NULL;
    return node->NodeElement;
}
Node get_Next_Node(Node node){
    if (node==NULL)
        return NULL;
    return node->Next;
}

Node get_First_Node(Linked_List list){
    if (list==NULL)
        return NULL;
    return list->First;
}
Node get_Last_Node(Linked_List list){
    if (list==NULL)
        return NULL;
    return list->Last;
}
int get_List_Size(Linked_List list){
    if (list==NULL)
        return 0;
    return list->List_Size;
}

void displayList(Linked_List list){
    if (list==NULL)
        return;
    if (list->List_Size==0)
        return;

    Node tmp=list->First;
    while (tmp!=NULL){
        list->printElement(tmp->NodeElement);
        tmp=tmp->Next;
    }
}







