#ifndef POKEMON_H
#define POKEMON_H

#include "Defs.h"

typedef struct pok_type_t* pok_type;
typedef struct pokemon_bio_t* pokemon_bio;
typedef struct pokemon_t* pokemon;


//species functions
pok_type create_Pokemon_type(char *name);
void destroy_Pokemon_type(pok_type type);
void print_pokemon_type(pok_type type);
void add_to_effective_against_me(pok_type me, pok_type other);
void add_to_effective_against_others(pok_type me, pok_type other);
void remove_from_effective_against_me(pok_type me, pok_type other);
void remove_from_effective_against_others(pok_type me, pok_type other);

//bio functions
pokemon_bio create_Pokemon_bio(double height, double weight, int attack);

//pokemon functions
pokemon create_Pokemon(char* pok_name, char* pok_species, double height, double weight, int attack, pok_type type);
void destroy_Pokemon(pokemon pok);
void print_pokemon(pokemon pok);

//types' functions
int get_num_of_pok_this_type(pok_type type);
char* get_name_of_type(pok_type type);
pok_type* get_effective_against_me(pok_type type);
int get_num_of_effective_against_me(pok_type type);
int get_num_of_effective_against_others(pok_type type);

//battle function
int equalpokemon(element e1,element e2);
element copyPokemon(element pokemon1);
int getAttackFunc(element firstElem,element secondElem,int* attackFirst,int* attackSecond);
char* getCategoryFunc(element e);

//pok_type copy_Pokemon_type(pok_type type);
//get functions
pok_type* get_effective_against_others(pok_type type);
pok_type* get_effective_against_me(pok_type type);
char* get_name_of_type(pok_type type);
int num_of_effective_against_others(pok_type type);
int num_of_effective_against_me(pok_type type);
int get_num_of_pok_this_type(pok_type type);
char* get_pok_name(pokemon pok);
char* get_pok_species(pokemon pok);
pok_type get_pok_type(pokemon pok);
void set_num_of_pok_this_type(pok_type type, int num);



#endif /* POKEMON_H */

