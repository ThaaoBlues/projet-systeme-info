#ifndef FONCTIONS_H
#define FONCTIONS_H
#include <stdint.h>

typedef struct FuncNode {
    unsigned int id;    
    char name[5];
    int value;      // Ligne de début
    int nb_args;    // Nombre d'arguments attendus
    struct FuncNode* next;
} FuncNode;

// Prototypes
uint32_t get_func(char name[5]);
int get_func_args(char name[5]);
void add_func(char name[5], int start_line, int nb_args);
void update_func_args(char name[5], int nb_args);

#endif