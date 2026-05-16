#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "fonctions.h"

#define HASH_SIZE 1024  
FuncNode* table_fonctions[HASH_SIZE];


int func_id_to_index(char var_name[5]){
	int index = 0;
	for(int i = 0;i<4;i++){
		index |= var_name[i] << (i*4);
	}
	return index;
}



// revoie la ligne à laquelle sauter pour appeler la fonction
uint32_t get_func(char name[5]) {
    unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index
    FuncNode* current = table_fonctions[hash_index];
    while(current) {
        if(current->id == full_id) return current->value;
        current = current->next;
    }
    return 0; // Variable non trouvée
}


void add_func(char name[5], int start_line, int nb_args){


    unsigned int full_id = func_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index

	FuncNode* new_node = malloc(sizeof(FuncNode));

    strcpy(new_node->name,name);
    new_node->value = start_line;
    new_node->id = full_id;

    if(table_fonctions[hash_index] == NULL){

		table_fonctions[hash_index] = new_node;


	}else{
		
		FuncNode* current = table_fonctions[hash_index];
		while(current-> next != NULL) {
			current = current->next;
		}
		current->next = new_node;

	}
}

int get_func_args(char name[5]) {
    unsigned int full_id = func_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    FuncNode* current = table_fonctions[hash_index];
    while(current) {
        if(strcmp(current->name, name) == 0) return current->nb_args;
        current = current->next;
    }
    return 0;
}



void update_func_args(char name[5],int nb_args){
    unsigned int full_id = func_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    FuncNode* current = table_fonctions[hash_index];
    while(current) {
        if(strcmp(current->name, name) == 0){
            current->nb_args = nb_args;
            
            return;
        }else{
            current = current->next;
        }
    }
    return 0;

}