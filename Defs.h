#ifndef DEFS_H_
#define DEFS_H_


typedef enum e_bool { false,true } bool;
typedef enum e_status { success,failure } status;
typedef void* element;

//functions
typedef element (*copyFunction)(element);
typedef status (*freeFunction)(element);
typedef status (*printFunction)(element);
typedef int (*equalFunction)(element,element);
typedef char* (*getCategoryFunction)(element);
typedef int (*getAttackFunction)(element firstElem, element secondElem, int* attackFirst, int* attackSecond);

#endif /* DEFS_H_ */
