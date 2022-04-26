#include "Max_Heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Heap_t{
    int Current_size;
    int Max_length;
    char* HeapName;
    element* TheHeap;

    equalFunction Compare;
    freeFunction freeElement;
    printFunction printElement;
    copyFunction copyElement;
};

Heap CreateHeap(int length, char* UniqueName,freeFunction freeElement,printFunction printElement,equalFunction Compare,copyFunction copyElement) {
    Heap newHeap = (Heap) malloc(sizeof(struct Heap_t));
    if (newHeap == NULL){
        printf("No memory available\n");
        return NULL;
    }
    newHeap->HeapName=(char*)malloc(strlen(UniqueName)+1);
    if (newHeap->HeapName==NULL){
        printf("No memory available\n");
        free(newHeap);
    	return NULL;
    }
    newHeap->TheHeap=(element*)malloc(length*sizeof(element));
    if (newHeap->TheHeap==NULL){
        printf("No memory available\n");
    	free(newHeap->HeapName);
    	free(newHeap);
    	return NULL;
    }


    strcpy(newHeap->HeapName,UniqueName);
    newHeap->Current_size=0;
    newHeap->Max_length=length;

    newHeap->Compare=Compare;
    newHeap->freeElement=freeElement;
    newHeap->printElement=printElement;
    newHeap->copyElement=copyElement;

    return newHeap;
}

void Max_Heapify(Heap heap,int index){
    int Left=2*index;
    int Right=2*index+1;
    int largest_index;

    if (Left <= heap->Current_size-1 && heap->Compare(heap->TheHeap[Left], heap->TheHeap[index]) == 1) {
        largest_index = Left;
    } else largest_index = index;
    if (Right <= heap->Current_size-1 && heap->Compare(heap->TheHeap[Right], heap->TheHeap[largest_index]) == 1){
        largest_index=Right;
    }
    if (largest_index!=index){
    	element tmp;
        tmp=heap->TheHeap[index];
        heap->TheHeap[index]=heap->TheHeap[largest_index];
        heap->TheHeap[largest_index]=tmp;
        Max_Heapify(heap,largest_index);
    }
}

status destroyHeap(Heap heap){
    if (heap==NULL){
        return success;
    }
    for (int i=0; i<heap->Current_size; i++){
        if (heap->TheHeap[i] != NULL)
            heap->freeElement(heap->TheHeap[i]);
    }
    if (heap->HeapName != NULL)
        free(heap->HeapName);
    free(heap->TheHeap);
    free(heap);
    heap=NULL;
    return success;
}

void Heap_Increase_Key(Heap heap,int index, element elem){
    if (heap->Compare(heap->TheHeap[(int)index/2],elem)==1) //if element < parent = done.
        return;

    element tmp;
    while (index>0 && heap->Compare(heap->TheHeap[(int)(index/2)],heap->TheHeap[index])==-1) {
        tmp=heap->TheHeap[(int)(index/2)];
        heap->TheHeap[(int)(index/2)]=heap->TheHeap[index];
        heap->TheHeap[index]=tmp;
        index=(int)(index/2);
    }
}

status insertToHeap(Heap heap, element elem){
    if (heap==NULL)
        return failure;
    if (elem==NULL && heap->Current_size == heap->Max_length)
        return failure;

    if (heap->Current_size == 0){
    	heap->Current_size++;
    	heap->TheHeap[0]=heap->copyElement(elem);
        return success;
    }

    heap->TheHeap[heap->Current_size]=heap->copyElement(elem);
    Heap_Increase_Key(heap, (heap->Current_size), elem);
    heap->Current_size++;
    return success;
}

element TopMaxHeap(Heap heap){
    if (heap==NULL)
        return NULL;
    if (heap->Current_size < 1)
        return NULL;
    if (heap->TheHeap[0]==NULL)
        return NULL;
    return (heap->TheHeap[0]);
}

element PopMaxHeap(Heap heap){
    element MaxElement = heap->copyElement(heap->TheHeap[0]);
    if (MaxElement==NULL)
        return NULL;

    heap->freeElement(heap->TheHeap[0]);
    heap->TheHeap[0]=heap->TheHeap[heap->Current_size - 1];
    heap->Current_size--;
    Max_Heapify(heap,0);
    return MaxElement;
}

char* getHeapId(Heap heap){
    if (heap==NULL)
        return NULL;
	if (heap->HeapName==NULL)
		return NULL;
	return heap->HeapName;
}

int getHeapCurrentSize(Heap heap){
    if (heap==NULL)
        return 0;
	return heap->Current_size;
}

Heap copy_Heap(Heap heap){
    Heap newHeap=CreateHeap(heap->Max_length,heap->HeapName,heap->freeElement,heap->printElement,heap->Compare,heap->copyElement);
    if (newHeap==NULL)
        return NULL;

    for (int i=0; i < heap->Current_size; i++){
        newHeap->TheHeap[i]=heap->copyElement(heap->TheHeap[i]);
    }
    newHeap->Current_size=heap->Current_size;
    return newHeap;
}

//typedef int (*equalFunction)(element,element);
int compare_heaps(Heap one,Heap other) {
    if (one == NULL && other == NULL)
        return 0;
    if (strcmp(one->HeapName,other->HeapName)==0)
        return 0;
    return -2;
}

status printHeap(Heap heap){
    if (heap==NULL)
        return failure;

    if (heap->Current_size == 0){
        printf("%s:\n",heap->HeapName);
        printf("No elements.\n\n");
        return success;
    }

    Heap newHeap=copy_Heap(heap);
    if (newHeap==NULL)
        return failure;

    printf("%s:\n",heap->HeapName);
    element tmp;


    for (int i=0; i<heap->Current_size ; ++i) {
        tmp=PopMaxHeap(newHeap);
        printf("%d. ",i+1);
        newHeap->printElement(tmp);
        newHeap->freeElement(tmp);
    }
    destroyHeap(newHeap);
    return success;
}



