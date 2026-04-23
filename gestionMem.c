#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "gestionMem.h"
#define HASH_SIZE 1024  

uint32_t derniere_addr_libre = 0x00000004;


struct Node* table[HASH_SIZE];
uint32_t profondeur_actuelle = 0;




void scopeDeeper(){profondeur_actuelle++;}

void scopeSmaller(){profondeur_actuelle--;}

// on prend une suite ascii d'octets
// on les mets les unes à la suite des autres pour former un int32
// ça donne une bijection des mots de 4 lettres vers les indexs sur 32 bits

int var_id_to_index(char var_name[5]){
	int index = 0;
	for(int i = 0;i<4;i++){
		index |= var_name[i] << (i*4);
	}
	return index;
}



// revoie le pointeur vers la memoire stoquant la variable
uint32_t get_var(char name[5]) {
    unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index
    struct Node* current = table[hash_index];
    while(current) {
        if(current->id == full_id && profondeur_actuelle >= current->profondeur) return current->pointeur;
        current = current->next;
    }
    return 0; // Variable non trouvée
}


char is_constante(char name[5]){
	unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index
    struct Node* current = table[hash_index];
    while(current) {
        if(current->id == full_id && profondeur_actuelle >= current->profondeur) return current->est_constante;
        current = current->next;
    }
    return -1; // Variable non trouvée

}



char is_pointeur(char name[5]){
	unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index
    struct Node* current = table[hash_index];
    while(current) {
        if(current->id == full_id && profondeur_actuelle >= current->profondeur) return current->est_pointeur;
        current = current->next;
    }
    return -1; // Variable non trouvée

}



uint32_t add_var(char name[5],char is_constante,char is_pointeur){
	/*
	Rajoute une variable dans la table des symboles
	*/
	unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index

	struct Node* new_node = malloc(sizeof(struct Node));
	
	


    if(table[hash_index] == NULL){

		table[hash_index] = new_node;


	}else{
		
		struct Node* current = table[hash_index];
		while(current-> next != NULL) {
			current = current->next;
		}
		current->next = new_node;

	}

	new_node->id = full_id;
	new_node->est_constante = is_constante;
    new_node->est_pointeur = is_pointeur;
	new_node->value = NULL;
	new_node->profondeur = profondeur_actuelle;
    strcpy(new_node->name,name);

	//new_node->est_constante = ???

	// on utilise les addresses de manière contigues
	// car rien ne nous en empèche contrairement aux indices dans la hashmap table
    
	new_node->pointeur = derniere_addr_libre;
	derniere_addr_libre++;

	//printf("[+] added variable %s\n",name);
	//printf("[c] check getvar %d\n", get_var(name));
    return new_node->pointeur;

}

// efface toutes les variables à cette profondeur
void free_scope(){


	for(int i =0;i<HASH_SIZE;i++){
		struct Node* current = table[i];
		struct Node* prec_node = NULL;
		while(current != NULL) {
			if(current->profondeur > profondeur_actuelle){
				
				// garbage collector
				derniere_addr_libre--;

				// ne pas oublier de refermer la chaine 
				// une fois que l'on a enlevé le maillon qui nous intéresse
				if(prec_node != NULL && current->next != NULL){
					prec_node->next = current->next;
				}

				// entrée de table des symboles
				free(current);

				
			}
			prec_node = current;
			current = current->next;

		}
	}
}

void printMem(){
    print_table(table);
}

char whichTmp = 0;
uint32_t adr[2] = {2,3}; // 
uint32_t getTmpAddr(){
    whichTmp = (whichTmp+1) %2;
    return adr[whichTmp];
}

/* FONCTION PAR GEMINI*/

// On suppose que ta structure et HASH_SIZE sont déjà définis au-dessus
// void print_table(struct Node* table[])

void print_table(struct Node* table[]) {
    printf("\n=== VISUALISATION DE LA MÉMOIRE (HASH TABLE) ===\n");
    printf("%-7s | %-18s | %s\n", "Index", "Value (0)", "Pointeur");
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < HASH_SIZE; i++) {
        // Affiche l'index du tableau
        if (table[i] != NULL){
            struct Node* current = table[i];
            while (current != NULL) {
                // On affiche l'ID et l'adresse du nœud actuel pour bien voir le lien
                printf("[ID:%u (%s) | Val:%d | @:%d] \n", 
                        current->id,
                        current->name, 
                        current->value, 
                        current->pointeur);
                
                
                current = current->next;
            }
        }
    }
    printf("---------------------------------------------------------------------------\n\n");
}