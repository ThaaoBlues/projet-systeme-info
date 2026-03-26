%{
#include <stdlib.h>
#include <stdio.h>
#include "gestionMem.h"

#define VAR_NAME_SIZE 4
#define TAILLE_BANC_REGISTRES





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
%token tEGAL tPO tPF tSOU tADD tDIV tMUL tERROR tMAIN tCONST tINTVAR tSEP tENDLINE tENDINST tPRINTF tEXP tACCO tACCF
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
	| tINTVAR GroupedDecl tENDINST {printf("on a déclaré un/des nombre(s) entier(s)\n");}
	| tPRINTF Expr tENDINST {fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",$2,$2);}; // PB DE PRINT DE VALEUR RANDOM


// premier tSEP représente un espace, le second soit une virgule soit un espace
// la variable va pointer sur le dernier résultat calculé
																								// COPIE de resultat dans la variable
GroupedDecl : tSEP tKEYWORD tSEP GroupedDecl {uint32_t allocated_addr = add_var($2); fprintf(output_file, "5 %d %d ;Copie de %d dans %d\n",allocated_addr,RESULT_MEM_ADDR,RESULT_MEM_ADDR,allocated_addr);}
	| tEGAL tSEP Expr {$$ = $3;};
 

Expr :  tPO Expr tPF
		| Expr tADD DivMul {
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "1 %d %d %d ; Addition \n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR;}
		| Expr tSOU DivMul { 
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "3 %d %d %d ; Soustraction \n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| DivMul { $$ = $1; } ;
DivMul :	  DivMul tMUL Terme {
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "2 %d %d %d ; Multiplication\n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| DivMul tDIV Terme { 
            // On écrit dans le fichier au lieu de la console
            fprintf(output_file, "4 %d %d %d ; Division\n", RESULT_MEM_ADDR, $1, $3); 
            $$ = RESULT_MEM_ADDR; }
		| Terme { $$ = $1; } ;
Terme : tKEYWORD { uint32_t ret = get_var($1); fprintf(output_file, "; Addr %d est la variable %s\n",ret, $1); $$ = ret; }
		// 6 = AFC (affectation)
		| tNB {uint32_t tmpAddr = getTmpAddr(); fprintf(output_file, "6 %d %d ; Constate %d dans addresse temporaire %d\n", tmpAddr, $1, $1, tmpAddr); $$=tmpAddr;} ;

%%

