%{
#include <stdlib.h>
#include <stdio.h>
#define HASH_SIZE 1024  // Tu peux monter à 65536 si tu veux être large
#define VAR_NAME_SIZE 4
#define TAILLE_BANC_REGISTRES

uint32_t dernière_addr_libre = 0x00000000;
extern FILE *output_file;

int next_free_address = 1000;
int new_tmp() { return next_free_address++; }

// on travaille avec une pile
void free_tmp() {next_free_address++;}
%}


struct Node {
    unsigned int id;    // Ton index calculé sur 32 bits
    int value;
	uint32_t pointeur;
	uint32_t profondeur;
    struct Node* next;  // Pour gérer si deux noms tombent sur la même case
	bool est_constante;
};

struct Node* table[HASH_SIZE];
uint32_t profondeur_actuelle = 0;

int get_var(char name[5]) {
    unsigned int full_id = var_id_to_index(name);
    int hash_index = full_id % HASH_SIZE;
    
    // On cherche dans la liste chaînée à cet index
    struct Node* current = table[hash_index];
    while(current) {
        if(current->id == full_id && profondeur_actuelle >= current->profondeur) return current->value;
        current = current->next;
    }
    return 0; // Variable non trouvée
}

void add_var(char name[5], int value){
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
	new_node->value = value;
	new_node->profondeur = profondeur_actuelle;

	//new_node->est_constante = ???

	// on utilise les addresses de manière contigues
	// car rien ne nous en empèche contrairement aux indices dans la hashmap table
	new_node->pointeur = derniere_addresse_libre;
	derniere_address_libre++;

	printf("[+] added variable %s=%d\n",name,value);
	printf("[c] check getvar %d\n", get_var(name));

}

// efface toutes les variables à cette profondeur
void free_scope(){


	for(int i =0;i<HASH_SIZE;i++){
		struct Node* current = table[hash_index];
		struct Node* prec_node = NULL;
		while(current != NULL) {
			if(current->profondeur > pronfondeur_actuelle){
				free(current);

				// ne pas oublier de refermer la chaine 
				// une fois que l'on a enlevé le maillon qui nous intéresse
				if(prec_node != NULL && current->next != NULL){
					prec_node->next = current->next;
				}

				
			}
			prec_node = current;
			current = current->next;

		}
	}
}


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



void yyerror(char *s);
%}
%union { int nb; char var[5]; }
%token tEGAL tPO tPF tSOU tADD tDIV tMUL tERROR tMAIN tCONST tINTVAR tSEP tENDLINE tENDINST tPRINTF tEXP tACCO tACCF
%token <nb> tNB
%token <var> tID tKEYWORD
%type <nb>  Expr DivMul Terme GroupedDecl
%start Main
%%
Main : tMAIN tPO tPF tACCO Body tACCF {printf("FNISHED MAIN BODY\n");};

Body:
 	tACCO {profondeur_actuelle = profondeur_actuelle +1;} Body {profondeur_actuelle = profondeur_actuelle -1;free_scope();} tACCF 
	| Instruction Body {}
	| {printf("body terminé, on remonte.\n");};
	
Instruction : tCONST GroupedDecl tENDINST {}
	| tINTVAR GroupedDecl tENDINST {printf("on a déclaré un/des nombre(s) entier(s)\n");}
	| tPRINTF Expr tENDINST {printf("printf() : %d\n",$2);};


// premier tSEP représente un espace, le second soit une virgule soit un espace
GroupedDecl : tSEP tKEYWORD tSEP GroupedDecl {$$ = $4; add_var($2,$4);}
	| tEGAL tSEP Expr {$$ = $3;};
 

Expr :  tPO Expr tPF {$$ = $2;} 
		| Expr tADD DivMul { int res = new_tmp();
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "1 %d %d %d\n", res, $1, $3); 
            $$ = res;}
		| Expr tSOU DivMul { int res = new_tmp();
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "3 %d %d %d\n", res, $1, $3); 
            $$ = res; }
		| DivMul { $$ = $1; } ;
DivMul :	  DivMul tMUL Terme { int res = new_tmp();
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "2 %d %d %d\n", res, $1, $3); 
            $$ = res; }
		| DivMul tDIV Terme { int res = new_tmp();
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "4 %d %d %d\n", res, $1, $3); 
            $$ = res; }
		| Terme { $$ = $1; } ;
Terme :		  tPO Expr tPF { $$ = $2; }
		| tKEYWORD { $$ = get_var($1); }
		| tNB { $$ = $1; printf("Terme = %d\n",$1);} ;

%%

