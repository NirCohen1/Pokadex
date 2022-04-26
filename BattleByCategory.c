#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "BattleByCategory.h"
#include "Linked_List.h"
#include "Max_Heap.h"

struct battle_s{
	int capacity;
	int numberOfCategories;
	char* categories;
//functions pointers
	equalFunction equalElement; //compare 2 char*
	copyFunction copyElement; // copy pokemon
	freeFunction freeElement; //free pokemon
	getCategoryFunction getCategory; //get pokemon category
	getAttackFunction getAttack;
	printFunction printElement;
//linked list heap
    Linked_List heap_list;
};

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement) {

    Battle newBattle = (Battle) malloc(sizeof(struct battle_s));
    if (newBattle == NULL) {
        printf("No memory available\n");
        return NULL;
    }
    newBattle->categories=(char*)malloc(strlen(categories)+1);
    if (newBattle->categories==NULL){
        printf("No memory available\n");
        free(newBattle);
        return NULL;
    }
    strcpy(newBattle->categories, categories);
    newBattle->capacity = capacity;
    newBattle->numberOfCategories = numberOfCategories;
    newBattle->equalElement = equalElement;
    newBattle->copyElement = copyElement;
    newBattle->freeElement = freeElement;
    newBattle->getCategory = getCategory;
    newBattle->getAttack = getAttack;
    newBattle->printElement = printElement;
    newBattle->heap_list = createLinkedList((FreeFun) destroyHeap, (CopyFun) copy_Heap, (CompareFun) compare_heaps, (PrintFun) printHeap, (GetCategory) getHeapId);
    // create link list print not enough memory
    if (newBattle->heap_list == NULL){
        free(newBattle->categories);
        free(newBattle);
        return NULL;
    }

    char* buffer= strdup(categories);
    char* type;
    char *pos;
    type = strtok(buffer,",");

    if ((pos = strchr(buffer, '\n')) != NULL)
        *pos = '\0';
    if ((pos = strchr(buffer, '\r')) != NULL)
        *pos = '\0';

    for (int i = 0; i < newBattle->numberOfCategories; i++) {

        Heap battle_heap=CreateHeap(capacity,type,freeElement,printElement,equalElement,copyElement);
        status returned_val=appendNode(newBattle->heap_list,battle_heap);

        if (battle_heap==NULL) {
            destroyList(newBattle->heap_list);
            free(newBattle->categories);
            free(newBattle);
            return NULL;
        }

        if (returned_val==failure) {
            destroyList(newBattle->heap_list);
            free(newBattle->categories);
            free(newBattle);
            return NULL;
        }
        type=strtok(NULL,",");

        if(type!=NULL && (pos=strchr(type, '\n'))!=NULL)
            *pos='\0';
        if(type!=NULL &&(pos=strchr(type, '\r'))!=NULL)
            *pos='\0';
    }
    free(buffer);
    return newBattle;
}

status insertObject(Battle b, element elem) {
    if (b == NULL)
        return failure;
    if (get_List_Size(b->heap_list) == 0)
        return failure;

    char* category=b->getCategory(elem);

    Node node = (Node)searchByKeyInList(b->heap_list,category); //(linked list ,char*), get category of pokemon
    if (node==NULL){
    	return failure;
    }

    if (getHeapCurrentSize(get_Element(node)) >= b->capacity){
        printf("Type at full capacity.\n");
    	return failure;
    }
    status returned_val=insertToHeap(get_Element(node),elem);
    return returned_val;
}

element removeMaxByCategory(Battle b,char* category) {
    if (b == NULL)
        return 0;
    if(get_List_Size(b->heap_list) == 0)
    	return 0;
    //search name
    Node tmp=get_First_Node(b->heap_list);
    if (strcmp(category, getHeapId(get_Element(tmp))) == 0) {
    	if(getHeapCurrentSize(get_Element(tmp) == 0))
    		return 1;
        return PopMaxHeap(get_Element(tmp));
    }
    while (get_Next_Node(tmp) != NULL) {
        tmp = get_Next_Node(tmp);
        if (strcmp(category, getHeapId(get_Element(tmp))) == 0) {
            if (getHeapCurrentSize(get_Element(tmp))==0)
                return (element) 1;
            //// There‬‬ ‫‪is‬‬ ‫‪no‬‬ ‫‪Pokemon‬‬ ‫‪to‬‬ ‫‪remove. (main second)‬‬
            return PopMaxHeap(get_Element(tmp));
        }
    }
    return 0;
}

int getNumberOfObjectsInCategory(Battle b,char* category){
    if (b==NULL)
        return 0;
    if (get_List_Size(b->heap_list)==0)
        return 0;

//search name
    Node tmp=get_First_Node(b->heap_list);
    // if contain one node (one category)
    if (strcmp(getHeapId(get_Element(tmp)), category) == 0)
        return getHeapCurrentSize(get_Element(tmp));
    //check every node (every category)
    while (get_Next_Node(tmp)!=NULL) {
        tmp = get_Next_Node(tmp);
        if (strcmp(getHeapId(get_Element(tmp)), category) == 0)
            return getHeapCurrentSize(get_Element(tmp));
    }
    return 0;
}

element fight(Battle b,element elem){
    if (b == NULL){
        printf("There are no Pokemons to fight against you.\n");
        return NULL;
    }
    if (get_List_Size(b->heap_list) == 0){
        printf("There are no Pokemons to fight against you.\n");
        return NULL;
    }

    int* attackFirst=(int*)malloc(sizeof(int));
    int* attackSecond=(int*)malloc(sizeof(int));
    int Attack_difference = 0;
    element My_fighter, Fighter;

    Node node = get_First_Node(b->heap_list);
    Heap heap = (Heap) get_Element(node);
    My_fighter=TopMaxHeap(heap);

    if(My_fighter!=NULL)
    	Attack_difference=b->getAttack(My_fighter,elem,attackFirst,attackSecond)-b->getAttack(elem,My_fighter,attackFirst,attackSecond);
    while (get_Next_Node(node)!=NULL){
		node=get_Next_Node(node);
		heap = (Heap) get_Element(node);
		Fighter=TopMaxHeap(heap);
		if (Fighter!=NULL){
			if (My_fighter==NULL)
				My_fighter=Fighter;
			else {
				//check attack of every element
				*attackFirst=b->getAttack(My_fighter ,elem,attackFirst,attackSecond);
				*attackSecond=b->getAttack(Fighter ,elem,attackFirst,attackSecond);
		    	Attack_difference=b->getAttack(My_fighter,elem,attackFirst,attackSecond)-b->getAttack(elem,My_fighter,attackFirst,attackSecond);
				if (*attackSecond>*attackFirst)
					My_fighter=Fighter;
			}
		}
	}
	if (My_fighter == NULL){
		printf("There are no Pokemons to fight against you.\n");
		free(attackFirst);
		free(attackSecond);
		return NULL;
	}

	Attack_difference=b->getAttack(My_fighter,elem,attackFirst,attackSecond)-b->getAttack(elem,My_fighter,attackFirst,attackSecond);
    printf("The final battle between:\n");
    b->printElement(elem);

    printf("In this battle his attack is :%d\n\n", b->getAttack(elem,My_fighter,attackFirst,attackSecond));
    printf("against ");
    b->printElement(My_fighter);
    printf("In this battle his attack is :%d\n\n", b->getAttack(My_fighter,elem,attackFirst,attackSecond));

    if (Attack_difference > 0){
        printf("THE WINNER IS:\n");
        b->printElement(My_fighter);
        free(attackFirst);
		free(attackSecond);
        return elem;
    }

    if (Attack_difference < 0){
        printf("THE WINNER IS:\n");
        b->printElement(elem);
        free(attackFirst);
		free(attackSecond);
        return My_fighter;
    }

    printf("IT IS A DRAW.\n");

    free(attackFirst);
    free(attackSecond);
    return My_fighter;
}

status destroyBattleByCategory(Battle b){
    if (b==NULL)
        return success;

    if (b->heap_list!=NULL)
        destroyList(b->heap_list);
    if (b->categories!=NULL)
        free(b->categories);
    free(b);
    return success;
}

void displayObjectsByCategories(Battle b){
    displayList(b->heap_list);
}
