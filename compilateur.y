%{
#include <stdlib.h>
#include <stdio.h>
#include "gestionMem.h"
#include "file_utils.h"

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

%token tEGAL tPO tPF tSOU tADD tDIV tMUL tVIRG tERROR tMAIN tCONST tINTVAR tSEP tENDLINE tENDINST tPRINTF tEXP tACCO tACCF tIF tELSE tWHILE
%token <nb> tNB
%token <var> tID tKEYWORD
%type <nb>  Expr DivMul Terme GroupedDecl GroupedDeclConst GroupedDeclConstPointeur GroupedDeclPointeur
%start Main

%%

Main : {iniOutputFile();}tMAIN tPO tPF tACCO Body tACCF {printf("FNISHED MAIN BODY\n");printMem();fclose(output_file);};

Body:
 	tACCO {scopeDeeper();} Body {scopeSmaller();free_scope();} tACCF 
	| Instruction Body {}
	| {printf("body terminé, on remonte.\n");};

	
Instruction : | tCONST tMUL GroupedDeclConstPointeur tENDINST //declaration de pointeur constant
    | tINTVAR tMUL GroupedDeclPointeur tENDINST //declaration de pointeur 
    | tCONST GroupedDeclConst tENDINST {prtinf("on déclare un/des constante");} 
	| tINTVAR GroupedDecl {printf("on a déclaré un/des nombre(s) entier(s)\n");}
	| tKEYWORD tEGAL Expr tENDINST{if is_constante($1){printf("ERREUR IMPOSSIBLE DE CHANGER CONSTANTE\n");}else{uint32_t allocated_addr = get_var($1); fprintf(output_file, "5 %d %d ;Copie de %d dans %d\n",allocated_addr,$3,$3,allocated_addr);}} 
	| tPRINTF Expr tENDINST{fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",$2,$2);} 
	| tIF Expr {
        fprintf(output_file,"; Debut IF %d",ftell_line(output_file,ftell(f)));
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(f))); // stoque la position du if
    } Body  {
        int lineJump = ftell_line(output_file,ftell(1))+1; // prend notre position
        fseek_line(output_file,pop(pile_lignes_a_finir)); // revient sur le if pour jump neq à notre position
        fprintf(output_file,"8 %d %d\n",$1,lineJump); // écris
        fseek(output_file,0,SEEK_END); // reviens à la fin du fichier
    } 
    | tIF Expr {
        fprintf(output_file,"; Debut IF %d avec ELSE",ftell_line(output_file,ftell(f)));
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(f))); // stoque la position du if
    } Body {
        int lineJump = ftell_line(output_file,ftell(f))+1; // prend notre ligne actuelle (fin de corps du if)
        fseek_line(output_file,pop(pile_lignes_a_finir)); // saute à la ligne du debut du if
        fprintf(output_file,"8 %d %d\n",$1,lineJump); // écris de jump par dessus le body dans l'instruction if
        fseek(output_file,0,SEEK_END); // reviens à la fin actuelle du fichier
    }  tELSE  {
        fprintf(output_file,"; Debut Else %d ",ftell_line(output_file,ftell(f))); 
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(f))); // stoque la ligne du début de body else
    }Body {
        int lineJump = ftell_line(output_file,ftell(f))+1; // prend notre ligne actuelle +1
        fseek_line(output_file,pop(pile_lignes_a_finir)); // reviens au début du else
        fprintf(output_file,"7 %d\n",lineJump); // écris de sauter par dessus le else (pour si on vient du if plus haut)
        seek(output_file,0,SEEK_END); // reviens à notre position d'écriture en fin de fichier
    } 

	// TODO FINIR IF AVEC LE SEEK QUI DOIT BIEN SE DEPLACER
	// ftell +1 ne marche pas /!\ 

    // ATTENTION, a la fin du IF refaire un fseek pour se remettre a la fin du fichier (j'ai tenter un fseek(-1))

    // ATTENTION, remplacer fseek car donne octet, trouver fonction qui donne la ligne (désoler j'avais pas internet dans le train)

    // ATTENTION, pour le else, on doit placer le jump juste avant le else, et le jump du if doit arriver a la premiere instru du body du else
    
    //Pour le if else, la partie if est la meme que if simple. Il faut rajouter un jump juste avant le else qui jump focement
    // sous le else. Pour cela, on parse le Else, on revient juste avant celui-ci et on ajoute un jump vers apres sa fin
    | tWHILE Expr  {
        printf(output_file,"Debut WHILE %d",ftell_line(output_file,ftell(f)));
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(f)));
    } Body {
        int line_while = pop(pile_lignes_a_finir);
        fprintf(output_file,"7 %d \n",pile_lignes_a_finir); 
        int lineJump = ftell_line(output_file,ftell(f))+1;
        fseek_line(output_file,line_while);
        fprintf(output_file,"8 %d %d\n",$1,lineJump);
        fseek(output_file,0,SEEK_END);
    };
    // Pour le while, on realise un jump hors de la boucle en début de while si l'instruction est fausse. A la fin du while on jump au debut du while pour reverifier la condition

// la variable va pointer sur le dernier résultat calculé
																								// COPIE de resultat dans la variable
GroupedDecl : tKEYWORD tVIRG GroupedDecl {uint32_t allocated_addr = add_var($1,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDecl {uint32_t allocated_addr = add_var($1,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init variable) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};

// declaration de constante. Ces declaration sont tres similaire a celle des variable a l'exception que l'on ne puisse pas les réaffecters.
GroupedDeclConst : tKEYWORD tVIRG GroupedDeclConst {uint32_t allocated_addr = add_var($1,1); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDeclConst {uint32_t allocated_addr = add_var($1,1); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};

GroupedDeclPointeur : tKEYWORD tVIRG GroupedDeclPointeur {uint32_t allocated_addr = add_var($1,0); fprintf(output_file, "4 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDeclPointeur {uint32_t allocated_addr = add_var($1,0); fprintf(output_file, "4 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init Pointeur) Pointeur %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};

GroupedDeclConstPointeur : : tKEYWORD tVIRG GroupedDeclConstPointeur {uint32_t allocated_addr = add_var($1,1); fprintf(output_file, "4 %d %d ;DECL POINTEUR CONSTANTE %s : (init par Affectation de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDeclConstPointeur {uint32_t allocated_addr = add_var($1,1); fprintf(output_file, "4 %d %d ;DECL POINTEUR CONSTANT %s : (init par Affectation de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init Pointeur CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};



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

