%{
#include <stdlib.h>
#include <stdio.h>
#include "gestionMem.h"

#define VAR_NAME_SIZE 4
#define TAILLE_BANC_REGISTRES


typedef struct Node {
    int numero_ligne;
    struct Node* next;
} Node;

typedef struct {
    Node* top; // Pointeur vers le haut de la pile
} Stack;


void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (s->top == NULL) {
        printf("La pile est vide !\n");
        return -1; 
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

Stack pile_lignes_a_finir = (*Node) malloc(sizeof(Node));


FILE *output_file = NULL;
void iniOutputFile(){
 	output_file = fopen("sortie.asm","w");

  	if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
}


void yyerror(char *s);
%}
%union { int nb; char var[5]; }
%token tEGAL tPO tPF tSOU tADD tDIV tMUL tVIRG tERROR tMAIN tCONST tINTVAR tSEP tENDLINE tENDINST tPRINTF tEXP tACCO tACCF tIF tELSE
%token <nb> tNB
%token <var> tID tKEYWORD
%type <nb>  Expr DivMul Terme GroupedDecl
%start Main
%%

Main : {iniOutputFile();}tMAIN tPO tPF tACCO Body tACCF {printf("FNISHED MAIN BODY\n");printMem();fclose(output_file);};

Body:
 	tACCO {scopeDeeper();} Body {scopeSmaller();free_scope();} tACCF 
	| Instruction Body {}
	| {printf("body terminé, on remonte.\n");};
	
Instruction : tCONST GroupedDecl tENDINST {} //TODO FAIRE LA CONSTANTE
	| tINTVAR GroupedDecl {printf("on a déclaré un/des nombre(s) entier(s)\n");}
	| tKEYWORD tEGAL Expr tENDINST{uint32_t allocated_addr = get_var($1); fprintf(output_file, "5 %d %d ;Copie de %d dans %d\n",allocated_addr,$3,$3,allocated_addr);} 
	| tPRINTF Expr tENDINST{fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",$2,$2);} 
	| tIF Expr {fprintf(output_file,"Debut IF %d",ftell(output_file));push(pile_lignes_a_finir,ftell(output_file))} Body {int lineJump = ftell(output_file)+1 ;fseek(output_file,pop(pile_lignes_a_finir)); fprintf(output_file,"8 %d %d\n",$1,lineJump);};
	// TODO FINIR IF AVEC LE SEEK QUI DOIT BIEN SE DEPLACER
	// ftell +1 ne marche pas /!\


// premier tSEP représente un espace, le second soit une virgule soit un espace
// la variable va pointer sur le dernier résultat calculé
																								// COPIE de resultat dans la variable
GroupedDecl : tKEYWORD tVIRG GroupedDecl {uint32_t allocated_addr = add_var($1); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDecl {uint32_t allocated_addr = add_var($1); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init variable) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};

Expr :  tPO Expr tPF {$$ = $2;}
		| Expr tADD DivMul {
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "1 %d %d %d ; Addition \n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR;}
		| Expr tSOU DivMul { 
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "3 %d %d %d ; Soustraction \n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| DivMul { $$ = $1;} ;
DivMul :	  DivMul tMUL Terme {
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "2 %d %d %d ; Multiplication\n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| DivMul tDIV Terme { 
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "4 %d %d %d ; Division\n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| Terme { $$ = $1;} ;
Terme : tKEYWORD { uint32_t ret = get_var($1); fprintf(output_file, "; Addr %d est la variable %s\n",ret, $1); $$ = ret; }
		// 6 = AFC (affectation)
		| tNB {uint32_t tmpAddr = getTmpAddr(); fprintf(output_file, "6 %d %d ; Constante %d dans addresse temporaire %d\n", tmpAddr, $1, $1, tmpAddr);$$=tmpAddr;} ;

%%

