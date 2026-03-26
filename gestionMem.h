#include <stdint.h>

#define RESULT_MEM_ADDR 0x00000001


struct Node {
    unsigned int id;    // Ton index calculé sur 32 bits
    char name[5];
    int value;
	uint32_t pointeur;
	uint32_t profondeur;
    struct Node* next;  // Pour gérer si deux noms tombent sur la même case
	char est_constante; 
};

void printMem();
int var_id_to_index(char var_name[5]);

uint32_t get_var(char name[5]);

uint32_t add_var(char name[5]);

void free_scope();


void scopeDeeper();
void scopeSmaller();

uint32_t getTmpAddr();