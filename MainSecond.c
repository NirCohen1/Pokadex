#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BattleByCategory.h"
#include "Pokemon.h"

int numberOfTypes=0;
int size_of_pokemon=0;
char* types;
int capacity=0;
pok_type* list_of_pTypes;
Battle newBattle=NULL;

void Print_all_Pokemons_by_Types(Battle battle){
    if (battle==NULL)
        return;
    displayObjectsByCategories(battle);
}

void Print_all_Pokemons_Types(){
    for(int i=0; i < numberOfTypes; i++){
        print_pokemon_type(list_of_pTypes[i]);
    }
}

void Insert_Pokemon_to_battles_training_camp(Battle battle){
    char buffer[300];
    char pok_type_entered[300];
    char pok_name[300];
    char pok_species[300];
    double pok_height;
    double pok_weight;
    int pok_attack;
    pok_type pokType=NULL;


    printf("Please enter Pokemon type name:\n");
    scanf("%s",pok_type_entered);
    for(int i=0; i < numberOfTypes; i++){
        if (strcmp(get_name_of_type(list_of_pTypes[i]),pok_type_entered)==0){
            pokType=list_of_pTypes[i];
            break;
        }
        if (i==numberOfTypes-1){
            printf("Type name doesn't exist.\n");
            return;
        }
    }
    if (get_num_of_pok_this_type(pokType)>=getNumberOfObjectsInCategory(battle,get_name_of_type(pokType))){
    	printf("Type at full capacity.\n");
    	return;
    }
    memset(buffer,'\0', sizeof(buffer));
    printf("Please enter Pokemon name:\n");
    scanf("%s",pok_name);

    printf("Please enter Pokemon species:\n");
    scanf("%s",pok_species);

    printf("Please enter Pokemon height:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    pok_height = atof(buffer);

    printf("Please enter Pokemon weight:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    pok_weight = atof(buffer);

    printf("Please enter Pokemon attack:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    pok_attack=atoi(buffer);
    pok_attack= (int)pok_attack;

    pokemon pok = create_Pokemon(pok_name,pok_species,pok_height,pok_weight,pok_attack,pokType);
    if(pok==NULL)
    	return;
    for(int h=0; h < numberOfTypes; h++){
		if(strcmp(pok_type_entered,get_name_of_type(list_of_pTypes[h]))==0) {
			set_num_of_pok_this_type(list_of_pTypes[h], get_num_of_pok_this_type(list_of_pTypes[h])+1);
			break;
		}
    }

    status returned_val=insertObject(battle,pok);
    if (returned_val==success) {
        printf("The Pokemon was successfully added.\n");
        print_pokemon(pok);
    }
}

void Remove_strongest_Pokemons_by_type(Battle battle){
    char buffer[300];
    printf("Please enter type name:\n");
    scanf("%s",buffer);
    element returned_val = removeMaxByCategory(battle,buffer);
    if (returned_val==0){
        printf("Type name doesn't exist.\n");
        return;
    }
    if ((int) returned_val == 1){
        printf("There are no Pokemons to remove.\n");
        return;
    }
    pokemon pok_val = (pokemon) returned_val;
    for(int h=0; h < numberOfTypes; h++){
		if(strcmp(get_name_of_type(get_pok_type(pok_val)),get_name_of_type(list_of_pTypes[h]))==0) {
			set_num_of_pok_this_type(list_of_pTypes[h], get_num_of_pok_this_type(list_of_pTypes[h])-1);
			break;
		}
	}
    printf("the strongest Pokemon was removed:\n");
    print_pokemon(returned_val);
    destroy_Pokemon(returned_val);
}

void Fight(){
    char buffer[300];
    char pok_name[300];
    char pok_species[300];
    double pok_height;
    double pok_weight;
    int* pok_attack=(int*)malloc(sizeof(int));
    int income_attack;
    pok_type pokType=NULL;

    printf("Please enter Pokemon type name:\n");
    scanf("%s",buffer);
    for(int i=0; i < numberOfTypes; i++){
        if (strcmp(get_name_of_type(list_of_pTypes[i]),buffer)==0){
            pokType=list_of_pTypes[i];
            break;
        }
        if (i==numberOfTypes-1){
            printf("Type name doesn't exist.\n");
            return;
        }
    }

    memset(buffer,'\0', sizeof(buffer));
    printf("Please enter Pokemon name:\n");
    scanf("%s",pok_name);

    printf("Please enter Pokemon species:\n");
    scanf("%s",pok_species);

    printf("Please enter Pokemon height:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    pok_height = atof(buffer);


    printf("Please enter Pokemon weight:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    pok_weight = atof(buffer);

    printf("Please enter Pokemon attack:\n");
    memset(buffer,'\0', sizeof(buffer));
    scanf("%s",buffer);
    income_attack=atoi(buffer);
    *pok_attack= income_attack;


    pokemon pok = create_Pokemon(pok_name,pok_species,pok_height,pok_weight,income_attack,pokType);
    if(pok==NULL){
        printf("No memory available.");
        return;
    }
    fight(newBattle,pok);
    free(pok_attack);
    destroy_Pokemon(pok);
}

void Exit(Battle battle){

    for(int i=0; i<numberOfTypes; i++) {
        destroy_Pokemon_type(list_of_pTypes[i]);
    }
    if (list_of_pTypes!=NULL)
    	free(list_of_pTypes);
    list_of_pTypes=NULL;
    destroyBattleByCategory(battle);

    printf("All the memory cleaned and the program is safely closed.");
}


int main(int argc, char *argv[]) {
    numberOfTypes = atoi(argv[1]);
    capacity = atoi(argv[2]);
    char *configurationFile = argv[3];
    
    //initialize function's variables and global variables
    char line[300];

    list_of_pTypes = (pok_type *) malloc(numberOfTypes * sizeof(pok_type));
    if (list_of_pTypes == NULL) {
        printf("No memory available\n");
        return -1;
    }


    //read data from file
    //TODO print something
    FILE *fp = fopen(configurationFile, "r");
    if (fp == NULL){
        free(list_of_pTypes);
        return -1;
    }
    char *pos;
    fgets(line, 300, fp);
    if ((pos = strchr(line, '\n')) != NULL)
        *pos = '\0';
    if ((pos = strchr(line, '\r')) != NULL)
        *pos = '\0';
    //types
    while (strcmp(line, "Types") != 0) {
        fgets(line, 300, fp);
        if ((pos = strchr(line, '\n')) != NULL)
            *pos = '\0';
        if ((pos = strchr(line, '\r')) != NULL)
            *pos = '\0';
    }
    fgets(line, 300, fp);

    char* SeperateLine1,*SeperateLine2;
    char* ME_OTHER;
    char* TypeWord;

    if((pos=strchr(line, '\n'))!=NULL)
        *pos='\0';
    if((pos=strchr(line, '\r'))!=NULL)
        *pos='\0';

    types=(char*)malloc(strlen(line)+1);
    strcpy(types,line);

    //check if the list of types not empty
    if(strcmp(line,"Pokemons")!=0){
        //read types and add to list_of_pTypes
        pok_type SomeType;
        TypeWord=strtok(line, ",");

        if(TypeWord!=NULL && (pos=strchr(TypeWord, '\n'))!=NULL)
            *pos='\0';
        if(TypeWord!=NULL &&(pos=strchr(TypeWord, '\r'))!=NULL)
            *pos='\0';

        //add to list_of_pTypes and types
        for(int i=0; i < numberOfTypes; i++){
            SomeType=create_Pokemon_type(TypeWord);
            list_of_pTypes[i]=SomeType;

            TypeWord=strtok(NULL,",");

            if(TypeWord!=NULL && (pos=strchr(TypeWord, '\n'))!=NULL)
                *pos='\0';
            if(TypeWord!=NULL &&(pos=strchr(TypeWord, '\r'))!=NULL)
                *pos='\0';
        }
    }
    //read effectiveness
    fgets(line, 300, fp);
    //copy the line to not change the original line
    char cp_line[300];
    int i=0;
    pok_type me=NULL;
    pok_type other=NULL;
    if(line!=NULL){
        strcpy(cp_line,line);
        if((pos=strchr(line, '\n'))!=NULL)
            *pos='\0';
        if((pos=strchr(line, '\r'))!=NULL)
            *pos='\0';
    }

    while( line!=NULL && strcmp(line,"Pokemons")!=0){
        i=0;
        memset(cp_line,'\0', sizeof(cp_line));
        strcpy(cp_line,line);
        TypeWord=strtok(line, "-");
        SeperateLine1=TypeWord;

        //loop to get the species after ":"
        while(TypeWord != NULL) {
            i++;
            TypeWord = strtok(NULL, "-");
            if(i==2)
                SeperateLine2=TypeWord;
        }

        TypeWord=strtok(SeperateLine1, " ");
        TypeWord=++TypeWord;
        ME_OTHER=strtok(SeperateLine2,":");

        if(strcmp(ME_OTHER,"me")==0){
            //add to against me
            char* TypeToAdd;
            TypeToAdd=strtok(cp_line,":");

            if(TypeToAdd!=NULL && (pos=strchr(TypeToAdd, '\n'))!=NULL)
                *pos='\0';
            if(TypeToAdd!=NULL &&(pos=strchr(TypeToAdd, '\r'))!=NULL)
                *pos='\0';

            while(TypeToAdd!=NULL){
                TypeToAdd=strtok(NULL,",");

                if(TypeToAdd!=NULL && (pos=strchr(TypeToAdd, '\n'))!=NULL)
                    *pos='\0';
                if(TypeToAdd!=NULL &&(pos=strchr(TypeToAdd, '\r'))!=NULL)
                    *pos='\0';

                //search me
                for(int s=0; s < numberOfTypes; s++){
                    if(strcmp(get_name_of_type(list_of_pTypes[s]),TypeWord)==0){
                        me=list_of_pTypes[s];
                        break;
                    }
                }

                //search other and add
                if(TypeToAdd!=NULL){
                    for(int s=0; s < numberOfTypes; s++){
                        if(strcmp(get_name_of_type(list_of_pTypes[s]),TypeToAdd)==0){
                            other=list_of_pTypes[s];
                            add_to_effective_against_me(me,other);
                            break;
                        }
                    }
                }
            }

        }
        if(strcmp(ME_OTHER,"other")==0){
            //add to against other
            char* TypeToAdd;
            TypeToAdd=strtok(cp_line,":");
            if(TypeToAdd!=NULL && (pos=strchr(TypeToAdd, '\n'))!=NULL)
                *pos='\0';
            if(TypeToAdd!=NULL &&(pos=strchr(TypeToAdd, '\r'))!=NULL)
                *pos='\0';
            while(TypeToAdd!=NULL){
                TypeToAdd=strtok(NULL,",");

                if(TypeToAdd!=NULL && (pos=strchr(TypeToAdd, '\n'))!=NULL)
                    *pos='\0';
                if(TypeToAdd!=NULL &&(pos=strchr(TypeToAdd, '\r'))!=NULL)
                    *pos='\0';

                //search me
                for(int s=0; s < numberOfTypes; s++){
                    if(strcmp(get_name_of_type(list_of_pTypes[s]),TypeWord)==0){
                        me=list_of_pTypes[s];
                        break;
                    }
                }
                //search other and add
                if(TypeToAdd!=NULL){
                    for(int s=0; s < numberOfTypes; s++){
                        if(strcmp(get_name_of_type(list_of_pTypes[s]),TypeToAdd)==0){
                            other=list_of_pTypes[s];
                            add_to_effective_against_others(me,other);
                            break;
                        }
                    }
                }
            }
        }
        fgets(line, 300, fp);
        strcpy(cp_line,line);
        if(line!=NULL && (pos=strchr(line, '\n'))!=NULL)
            *pos='\0';
        if(line!=NULL && (pos=strchr(line, '\r'))!=NULL)
            *pos='\0';
    }

    //we finally reach to pokemons
    //next line

    char *pokemon_name=NULL;
    char *pokemon_species = NULL;
    int inserted_attack = 0;
    double inserted_height = 0;
    double inserted_weight = 0;
    int counter=0;
    size_of_pokemon=0;
    char* inserted_somthing=NULL;
    pok_type inserted_type = NULL;
    pokemon new_pokemon;
    newBattle=createBattleByCategory(capacity, numberOfTypes, types, equalpokemon, copyPokemon, (freeFunction) destroy_Pokemon, getCategoryFunc, getAttackFunc,(printFunction) print_pokemon);

    //insert data
    while(fgets(line, sizeof(line), fp)!=NULL){
        counter=0;
        inserted_somthing=strtok(line,",");

        if((pos=strchr(line, '\n'))!=NULL)
            *pos='\0';
        if((pos=strchr(line, '\r'))!=NULL)
            *pos='\0';

        if(inserted_somthing!=NULL && (pos=strchr(inserted_somthing, '\n'))!=NULL)
            *pos='\0';
        if(inserted_somthing!=NULL &&(pos=strchr(inserted_somthing, '\r'))!=NULL)
            *pos='\0';

        while(inserted_somthing!=NULL){
            if(counter==0)
                pokemon_name=inserted_somthing;
            if(counter==1)
                pokemon_species=inserted_somthing;
            if(counter==2)
                inserted_height=atof(inserted_somthing);
            if(counter==3)
                inserted_weight=atof(inserted_somthing);
            if(counter==4)
                inserted_attack=atoi(inserted_somthing);
            if(counter==5){
                for(int h=0; h < numberOfTypes; h++){

                    if(inserted_somthing!=NULL && (pos=strchr(inserted_somthing, '\n'))!=NULL)
                        *pos='\0';
                    if(inserted_somthing!=NULL &&(pos=strchr(inserted_somthing, '\r'))!=NULL)
                        *pos='\0';

                    if(strcmp(inserted_somthing,get_name_of_type(list_of_pTypes[h]))==0) {
            			set_num_of_pok_this_type(list_of_pTypes[h], get_num_of_pok_this_type(list_of_pTypes[h])+1);
                        inserted_type = list_of_pTypes[h];
                        break;
                    }
                }
            }
            counter++;
            inserted_somthing=strtok(NULL,",");
        }

        new_pokemon = create_Pokemon(pokemon_name,pokemon_species,inserted_height,inserted_weight,inserted_attack,inserted_type);
        insertObject(newBattle,new_pokemon);
        destroy_Pokemon(new_pokemon);
    }

    free(types);
    fclose(fp);


    //show menu
    int choice=0;
    do
    {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons by types\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Insert Pokemnon to battles training camp\n");
        printf("4 : Remove stronger Pokemons by type\n");
        printf("5 : Fight\n");
        printf("6 : Exit\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                Print_all_Pokemons_by_Types(newBattle);
                break;
            case 2:
                Print_all_Pokemons_Types();
                break;
            case 3:
                Insert_Pokemon_to_battles_training_camp(newBattle);
                break;
            case 4:
                Remove_strongest_Pokemons_by_type(newBattle);
                break;
            case 5:
                Fight();
                break;
            case 6:
                Exit(newBattle);
                break;
            default:
                printf("Please choose a valid number.\n");
                break;
        }
    }while(choice!=6);
    return 0;
}
