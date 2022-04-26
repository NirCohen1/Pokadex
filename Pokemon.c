#include "Pokemon.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct pok_type_t {
    int num_of_pok_this_type;
    char* name_of_type;
    pok_type* effective_against_me;
    pok_type* effective_against_others;
    int num_of_effective_against_me;
    int num_of_effective_against_others;
};

struct pokemon_t {
    char* pokemon_name;
    char* pokemon_species;
    pok_type pokemon_type;
    pokemon_bio bio;
};

struct pokemon_bio_t {
    int attack;
    double height;
    double weight;
};
pok_type* get_effective_against_others(pok_type type){
	return type->num_of_effective_against_others;
}

pok_type* get_effective_against_me(pok_type type){
	return type->effective_against_me;
}

char* get_name_of_type(pok_type type){
	return type->name_of_type;
}

int get_num_of_pok_this_type(pok_type type){
	return type->num_of_pok_this_type;
}

char* get_pok_name(pokemon pok){
	return pok->pokemon_name;
}
char* get_pok_species(pokemon pok){
	return pok->pokemon_species;
}
pok_type get_pok_type(pokemon pok){
	return pok->pokemon_type;
}

void set_num_of_pok_this_type(pok_type type, int num){
	if(type!=NULL)
		type->num_of_pok_this_type=num;
}



//completed
pok_type create_Pokemon_type(char *name){
    pok_type new_type=malloc(sizeof(struct pok_type_t));
    if(new_type == NULL){
        return NULL;
    }

    new_type->name_of_type = malloc(strlen(name) + 1);
    if(new_type->name_of_type == NULL){
        free(new_type);
        return NULL;
    }
    strcpy(new_type->name_of_type, name);
    new_type->num_of_effective_against_me=0;
    new_type->num_of_effective_against_others=0;
    new_type->num_of_pok_this_type=0;
    new_type->effective_against_me=NULL;
    new_type->effective_against_others=NULL;
    return new_type;
}

//completed
void destroy_Pokemon_type(pok_type type){
    if(type == NULL)
        return;
    if(type->effective_against_me != NULL){
        free(type->effective_against_me);
        type->effective_against_me=NULL;
    }
    if(type->effective_against_others != NULL){
        free(type->effective_against_others);
        type->effective_against_others=NULL;
    }
    if(type->name_of_type != NULL){
        free(type->name_of_type);
        type->name_of_type=NULL;
    }
    free(type);
    type=NULL;
}

// completed
void print_pokemon_type(pok_type type) {
    printf("Type %s -- %d pokemons", type->name_of_type, type->num_of_pok_this_type);
    if (type->num_of_effective_against_me > 0) {
        printf("\n\tThese types are super-effective against %s:", type->name_of_type);
        for(int i=0; i<type->num_of_effective_against_me; i++) {
            printf("%s",type->effective_against_me[i]->name_of_type);
            if(i!=type->num_of_effective_against_me-1)
                printf(" ,");
        }
    }
    if (type->num_of_effective_against_others > 0) {
        printf("\n\t%s moves are super-effective against:", type->name_of_type);
        for(int i=0; i<type->num_of_effective_against_others; i++) {
            printf("%s", type->effective_against_others[i]->name_of_type);
            if(i!=type->num_of_effective_against_others-1)
                printf(" ,");
        }
    }
    printf("\n\n");
}

// completed
void add_to_effective_against_me(pok_type me, pok_type other){
    if(me->effective_against_me == NULL) {
        me->effective_against_me=(pok_type*)malloc(sizeof(pok_type));
        if(me->effective_against_me == NULL){
            return;
        }
        me->effective_against_me[me->num_of_effective_against_me]= other;
        me->num_of_effective_against_me++;
        return;
    }
    else{
        me->effective_against_me = (pok_type *) realloc(me->effective_against_me, sizeof(pok_type) * (me->num_of_effective_against_me + 1));
        if(me->effective_against_me == NULL){
            return;
        }

        me->effective_against_me[me->num_of_effective_against_me] = other;
        me->num_of_effective_against_me++;
        return;
    }
}
// completed
void add_to_effective_against_others(pok_type me, pok_type other) {
    if (me->effective_against_others == NULL) {
        me->effective_against_others = (pok_type *) malloc(sizeof(pok_type));
        if (me->effective_against_others == NULL) {
            return;
        }
        me->effective_against_others[me->num_of_effective_against_others] = other;
        me->num_of_effective_against_others++;
        return;
    } else {
        me->effective_against_others = (pok_type *) realloc(me->effective_against_others, sizeof(pok_type) *
                                                                                          (me->num_of_effective_against_others +
                                                                                           1));
        if (me->effective_against_others == NULL) {
            return;
        }

        me->effective_against_others[me->num_of_effective_against_others] = other;
        me->num_of_effective_against_others++;
        return;
    }
}
// completed
void remove_from_effective_against_me(pok_type me, pok_type other){
    for(int i=0; i < me->num_of_effective_against_me; i++){
        if(me->effective_against_me[i]==other){
            me->effective_against_me[i]=NULL;
            //move according to the insert's order
            for(int j=i+1;j<(me->num_of_effective_against_me)-1;j++){
                me->effective_against_me[j]=me->effective_against_me[j-1];
            }
        }
    }
    //realloc
    me->effective_against_me[(me->num_of_effective_against_me)-1]=NULL;
    me->effective_against_me=(pok_type*)realloc(me->effective_against_me, (me->num_of_effective_against_me - 1) * sizeof(pok_type*));
    if(me->effective_against_me==NULL)
        return;
    me->num_of_effective_against_me--;
}
// completed
void remove_from_effective_against_others(pok_type me, pok_type other) {
    if (me->effective_against_others == NULL)
        return;
    for (int i = 0; i < me->num_of_effective_against_others; i++) {
        if (strcmp(other->name_of_type, me->effective_against_others[i]->name_of_type) == 0) {
            for (; i < me->num_of_effective_against_others; i++) {
                if (i + 1 == me->num_of_effective_against_others) {
                    me->effective_against_others[i] = NULL;
                } else me->effective_against_others[i] = me->effective_against_others[i + 1];
            }
            me->num_of_effective_against_others--;
            if (me->num_of_effective_against_others == 0)
                if (me->effective_against_others != NULL) {
                    me->effective_against_others = NULL;
                }

            me->effective_against_others = (pok_type *)realloc(me->effective_against_others, sizeof(struct pok_type_t)*(me->num_of_effective_against_others));
            if (me->effective_against_others == NULL)
                return;
        }
    }
}
//completed
pokemon_bio create_Pokemon_bio(double height, double weight, int attack){
    pokemon_bio new_bio=(pokemon_bio) malloc(sizeof(struct pokemon_bio_t));
    if(new_bio==NULL){
        return NULL;
    }
    new_bio->attack=attack;
    new_bio->height=height;
    new_bio->weight=weight;
    return new_bio;
}
//completed
pokemon create_Pokemon(char pok_name[], char pok_species[],double height, double weight, int attack, pok_type type){
    pokemon new_pokemon;
    new_pokemon=(pokemon) malloc(sizeof(struct pokemon_t));
    if(new_pokemon==NULL){
        return NULL;
    }
    //pointer to the pokemon's species
    new_pokemon->pokemon_species = (char*)calloc(strlen(pok_species) + 1, sizeof(char));
    if(new_pokemon->pokemon_species == NULL){
        free(new_pokemon);
        return NULL;
    }
    strcpy(new_pokemon->pokemon_species, pok_species);
    //pointer to the pokemon's name
    new_pokemon->pokemon_name = (char*)calloc(strlen(pok_name)+1,sizeof(char));

    if(new_pokemon->pokemon_name==NULL){
        free(new_pokemon->pokemon_species);
        free(new_pokemon);
        return NULL;
    }
    strcpy(new_pokemon->pokemon_name,pok_name);
    new_pokemon->bio=create_Pokemon_bio(height, weight, attack);
    new_pokemon->pokemon_type=type;

    return new_pokemon;
}

//completed
void destroy_Pokemon(pokemon pok){
    if (pok==NULL)
        return;
    if(pok->pokemon_name!=NULL){
        free(pok->pokemon_name);
        pok->pokemon_name=NULL;
    }
    if(pok->pokemon_species != NULL){
        free(pok->pokemon_species);
        pok->pokemon_species=NULL;
    }
    if(pok->bio!=NULL){
        free(pok->bio);
        pok->bio=NULL;
    }
    free(pok);
    pok=NULL;
}

// completed
void print_pokemon(pokemon pok){
    if(pok==NULL)
        return;
    printf("%s :\n%s, %s.\nHeight: %.2lf m    Weight: %.2lf kg    Attack: %d\n\n", pok->pokemon_name,
           pok->pokemon_species, pok->pokemon_type->name_of_type, pok->bio->height, pok->bio->weight, pok->bio->attack);
}


//types' functions

int get_num_of_effective_against_me(pok_type type){
    if (type==NULL)
        return 0;

    return type->num_of_effective_against_me;
}

int get_num_of_effective_against_others(pok_type type){
    if (type==NULL)
        return 0;

    return type->num_of_effective_against_others;
}

//battle functions

//TODO change
int equalpokemon(element element1,element element2){
    pokemon pok1 = (pokemon) element1;
    pokemon pok2 = (pokemon) element2;

    if(pok1->bio->attack > pok2->bio->attack)
        return 1;
    if(pok1->bio->attack < pok2->bio->attack)
        return -1;
    return 0;
}

element copyPokemon(element pokemon1){
    if(pokemon1==NULL)
        return NULL;
    pokemon pok= (pokemon) pokemon1;
    pokemon newPok;
    newPok = create_Pokemon(pok->pokemon_name,pok->pokemon_species,pok->bio->height,pok->bio->weight,pok->bio->attack,pok->pokemon_type);
    if (newPok==NULL)
        return NULL;
    return (element) newPok;
}

int getAttackFunc(element firstElem,element secondElem,int* attackFirst,int* attackSecond){
    pokemon pok1 = (pokemon)firstElem;
    pokemon pok2 = (pokemon)secondElem;
    *attackFirst = pok1->bio->attack;

    int i=0;
    for (int i=0; i < pok1->pokemon_type->num_of_effective_against_me; i++){
    	if (strcmp(pok1->pokemon_type->effective_against_me[i]->name_of_type,pok2->pokemon_type->name_of_type)==0){
    		*attackFirst=*attackFirst-10;
    		break;
    	}
    }
    return *attackFirst;
}
char* getCategoryFunc(element element1){
    pokemon pok = (pokemon) element1;
    return pok->pokemon_type->name_of_type;
}
