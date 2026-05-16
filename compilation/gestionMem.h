#ifndef GESTION_MEM_H
    #include <stdint.h>

    #define RESULT_MEM_ADDR 0x00000001

    /*
    Structure représentant une variable
    */
    struct Node {
        unsigned int id;    // index calculé sur 32 bits
        char name[5];
        int value;
        uint32_t pointeur;
        uint32_t profondeur;
        struct Node* next;  // Pour gérer si deux noms tombent sur la même case
        char est_constante;
        char est_pointeur;
    }; 

    void printMem(); // fonction d'affichage claire de la mémoire utilisé pour comprendre ce qu'il se passe et ou se trouve l'addresse de tel valeur
    int var_id_to_index(char var_name[5]);

    uint32_t get_var(char name[5]);

    uint32_t add_var(char name[5],char is_constante,char is_pointeur);


    void free_scope();


    void scopeDeeper();
    void scopeSmaller();

    char is_constante(char name[5]);
    char is_pointeur(char name[5]);

    uint32_t getTmpAddr();

    void push_arg();

    void pop_arg();

    uint32_t get_sp();

    uint32_t get_next_free_addr();


    #define GESTION_MEM_H

#else

#endif