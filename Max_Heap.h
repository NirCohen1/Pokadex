#ifndef UNTITLED_MAX_HEAP_H
#define UNTITLED_MAX_HEAP_H
#include "Defs.h"

typedef struct Heap_t* Heap;

Heap CreateHeap(int length, char* UniqueName,freeFunction freeElement,printFunction printElement,equalFunction Compare,copyFunction copyElement);
void Max_Heapify(Heap heap,int index);
status destroyHeap(Heap heap);
status insertToHeap(Heap heap, element elem);
status printHeap(Heap heap);
Heap copy_Heap(Heap heap);

element TopMaxHeap(Heap heap);
element PopMaxHeap(Heap heap);
char* getHeapId(Heap heap);
int getHeapCurrentSize(Heap heap);
int compare_heaps(Heap one,Heap other);


#endif //UNTITLED_MAX_HEAP_H
