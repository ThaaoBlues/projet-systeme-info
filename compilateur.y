%{
#include <stdlib.h>
#include <stdio.h>
#include "file_utils.h"
#include "fonctions.h"

#define VAR_NAME_SIZE 4
#define TAILLE_BANC_REGISTRES


typedef struct StackNode {
    int numero_ligne;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top; // Pointeur vers le haut de la pile
} Stack;

//override de la fonction appeler par bison lors d'un tokken inatendu
void yyerror(const char *s) {
    extern int yylineno; // On récupère la variable de Flex
    fprintf(stderr, "ERREUR SYNTAXIQUE : %s à la ligne %d\n", s, yylineno);
}

void push(Stack* s, int value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    newNode->numero_ligne = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s) {
    if (s->top == NULL) {
        printf("La pile est vide !\n");
        return -1; 
    }
    StackNode* temp = s->top;
    int value = temp->numero_ligne;
    s->top = s->top->next;
    free(temp);
    return value;
}

Stack* pile_lignes_a_finir = NULL;


FILE *output_file = NULL;

void iniLineStack(){
    pile_lignes_a_finir = (Stack*) malloc(sizeof(Stack));
    pile_lignes_a_finir->top = NULL;
}

void iniOutputFile(){

    // we found not extremely inapropriate to init stack here as well
    iniLineStack();

 	output_file = fopen("sortie.asm","w+");

  	if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
}


%}
%union { int nb; char var[5]; }

%token tEGAL tPO tPF tSOU tADD tDIV tMUL tVIRG tAND tERROR tMAIN tCONST tINTVAR tSEP tENDLINE tENDINST tPRINTF tEXP tACCO tACCF tIF tELSE tWHILE tRETURN
%token <nb> tNB 
%token <var> tID tKEYWORD
%type <nb>  Expr DivMul Terme GroupedDecl GroupedDeclConst GroupedDeclConstPointeur GroupedDeclPointeur Args Params
%start Main

%%

// comme en C, on defini tout avant le main
Start : FunctionDefinitions Main ;



Main : {iniOutputFile();}tMAIN tPO tPF tACCO Body tACCF {printf("FNISHED MAIN BODY\n");printMem();fclose(output_file);};

Body:
 	tACCO {scopeDeeper();} Body {scopeSmaller();free_scope();} tACCF 
	| Instruction Body {}
	| {printf("body terminé, on remonte.\n");};

	
Instruction :
    | tKEYWORD tPO {

        // push l'adresse de retour avant les arguments

        // PLACEHOLDER, les arguments peuvent être des expr
        // on doit repasser après generation en ayant le bon offset
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file)));
        fprintf("PLACEHOLDER appel;                                                             \n",get_sp(),addr_ret);
        push_arg();

    } CallArgs tPF tENDINST { // function call without value affectation
        
        
        uint32_t addr_ret = ftell_line(output_file,fseek(output_file));
        fseek_line(output_file,pop(pile_lignes_a_finir));
        fprintf("5 %d %d ; (appel de fonction) on push l'adresse de retour",get_sp(),addr_ret);
        fseek(output_file,0,SEEK_END); // reviens à la fin actuelle du fichier

        uint32_t line_jump = get_func(tKEYWORD);
        fprintf(output_file,"7 %d; saut debut fontion\n",line_jump); 

    }

    | tRETURN Expr tENDINST {

        fprintf("5 %d %d ; stoque la valeur renvoyée par la fonction dans l'addr de resultat\n",RESULT_MEM_ADDR,$2);

    }
    | tCONST tMUL GroupedDeclConstPointeur //declaration de pointeur constant
    | tINTVAR tMUL GroupedDeclPointeur //declaration de pointeur 
    | tCONST GroupedDeclConst tENDINST {printf("on déclare un/des constante");} 
	| tINTVAR GroupedDecl {printf("on a déclaré un/des nombre(s) entier(s)\n");}
	| tKEYWORD tEGAL Expr tENDINST{
        if(is_constante($1)){
            printf("ERREUR : IMPOSSIBLE DE CHANGER LA VALEUR DE LA CONSTANTE : %s\n",$1);
        
        // suivi des pointeurs (necessaire car leur valeur doit être connue à la compilation)
        }else if (is_pointeur($1)) {
            uint32_t allocated_addr = get_var($1);
            fprintf(output_file, "5 %d %d ;Copie de %d dans le pointeur stocké à l'adresse %d\n",allocated_addr,$3,$3,allocated_addr);
        }else{
            uint32_t allocated_addr = get_var($1);
            fprintf(output_file, "5 %d %d ;Copie de %d dans la variable stockée à l'adresse %d\n",allocated_addr,$3,$3,allocated_addr);

        }
    } 
	| tPRINTF Expr tENDINST{
        
        fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",$2,$2);
    } 
    | error tENDINST { 
        yyerrok; //empeche bison de crash et continuer la compilation pour voir les autre erreur
        printf("Récupération de l'erreur effectuée. On continue l'analyse! \n");
    }
    
    

    | tIF Expr {
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); // stoque la position du if
        fprintf(output_file,"; Debut IF ligne %d avec ELSE                             \n",ftell_line(output_file,ftell(output_file)));
 
    } Body {
        // prend notre ligne actuelle (fin de corps du if)
        // +2 pour sauter le jump de else 
        int lineJump = ftell_line(output_file,ftell(output_file))+2;
        fseek_line(output_file,pop(pile_lignes_a_finir)); // saute à la ligne du debut du if
        fprintf(output_file,"8 %d %d ; jump conditionnel vers ligne %d\n",$2,lineJump,lineJump); // écris de jump par dessus le body dans l'instruction if
        fseek(output_file,0,SEEK_END); // reviens à la fin actuelle du fichier
    }  OptionalElse {};

	

    | tWHILE Expr  {
        int line_while_start = ftell_line(output_file,ftell(output_file));
        push(pile_lignes_a_finir,line_while_start);
        fprintf(output_file,";Debut WHILE %d                                             \n",line_while_start);
    } Body {
        int line_while = pop(pile_lignes_a_finir);
        fprintf(output_file,"7 %d; saut inconditionel pour remonter à la condition du while\n",line_while); 
        int lineJump = ftell_line(output_file,ftell(output_file))+1;
        fseek_line(output_file,line_while);
        fprintf(output_file,"8 %d %d; condition du while\n",$2,lineJump);
        fseek(output_file,0,SEEK_END);
    };
    // Pour le while, on realise un jump hors de la boucle en début de while si l'instruction est fausse. A la fin du while on jump au debut du while pour reverifier la condition




OptionalElse :
    tELSE {
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); // stoque la ligne du début de body else
        fprintf(output_file,"; Debut Else ligne %d                                                               \n",ftell_line(output_file,ftell(output_file))); 

    } Body {
        int lineJump = ftell_line(output_file,ftell(output_file)); // prend notre ligne actuelle
        fseek_line(output_file,pop(pile_lignes_a_finir)); // reviens au début du else
        fprintf(output_file,"7 %d ; saut inconditionnel vers la ligne %d pour éviter le else",lineJump,lineJump); // écris de sauter par dessus le else (pour si on vient du if plus haut)
        fseek(output_file,0,SEEK_END); // reviens à notre position d'écriture en fin de fichier
    } 

    |{
        int lineJump = ftell_line(output_file,ftell(output_file))+1;
        fprintf(output_file,"7 %d ; saut inconditionnel qui sert à rien pour avoir un offset de saut constant\n",lineJump,lineJump);};



        // la variable va pointer sur le dernier résultat calculé
// COPIE de resultat dans la variable
GroupedDecl : tKEYWORD tVIRG GroupedDecl {uint32_t allocated_addr = add_var($1,0,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDecl {uint32_t allocated_addr = add_var($1,0,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init variable) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};

// declaration de constante. Ces declaration sont tres similaire a celle des variable a l'exception que l'on ne puisse pas les réaffecters.
GroupedDeclConst : tKEYWORD tVIRG GroupedDeclConst {uint32_t allocated_addr = add_var($1,1,0); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);$$ = $3;}
	| tKEYWORD  GroupedDeclConst {uint32_t allocated_addr = add_var($1,1,0); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);$$ = $2;}
	| tEGAL Expr  tENDINST {$$ = $2;}
	| tENDINST {fprintf(output_file,"6 %d %d ; (Init CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);$$ = RESULT_MEM_ADDR;};


GroupedDeclPointeur : tKEYWORD tVIRG GroupedDeclPointeur {
        uint32_t allocated_addr = add_var($1,0,1); 
        fprintf(output_file, "5 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);
        $$ = $3;
    }
	| tKEYWORD  GroupedDeclPointeur {
        uint32_t allocated_addr = add_var($1,0,1); 
        fprintf(output_file, "5 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);
        $$ = $2;
    }

	| tEGAL Expr  tENDINST {$$ = $2;}

	| tENDINST {
        fprintf(output_file,"6 %d %d ; (Init Pointeur) Pointeur %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);
        $$ = RESULT_MEM_ADDR;
    };



GroupedDeclConstPointeur : tKEYWORD tVIRG GroupedDeclConstPointeur {
    uint32_t allocated_addr = add_var($1,1,1); 
    fprintf(output_file, "5 %d %d ;DECL POINTEUR CONSTANTE %s : (init par Affectation de %d dans %d)\n",allocated_addr,$3,$1,$3,allocated_addr);
    $$ = $3;
    }
	| tKEYWORD  GroupedDeclConstPointeur {
        uint32_t allocated_addr = add_var($1,1,1); 
        fprintf(output_file, "5 %d %d ;DECL POINTEUR CONSTANT %s : (init par Affectation de %d dans %d)\n",allocated_addr,$2,$1,$2,allocated_addr);
        $$ = $2;
    }
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


Terme : tKEYWORD tPO {

        // push l'adresse de retour avant les arguments

        // PLACEHOLDER, les arguments peuvent être des expr
        // on doit repasser après generation en ayant le bon offset
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file)));
        fprintf("PLACEHOLDER appel;                                                             \n",get_sp(),addr_ret);
        push_arg();

        } CallArgs tPF { // function call without value affectation
            
            // +1 pour compter le saut
            uint32_t addr_ret = ftell_line(output_file,fseek(output_file)) +1;
            fseek_line(output_file,pop(pile_lignes_a_finir));
            fprintf("5 %d %d ; (appel de fonction) on push l'adresse de retour",get_sp(),addr_ret);
            fseek(output_file,0,SEEK_END); // reviens à la fin actuelle du fichier

            uint32_t line_jump = get_func(tKEYWORD);
            fprintf(output_file,"7 %d; saut debut fontion\n",line_jump);

            // le resultat d'evaluation la fonction est toujours contenu dans RESULT_MEM_ADDR
            $$ = RESULT_MEM_ADDR;
        }

        | tKEYWORD { // variable 
            uint32_t ret = get_var($1); 
            fprintf(output_file, "; Addr %d est la variable %s\n",ret, $1); 
            $$ = ret; 
        }
		// 6 = AFC (affectation)
		| tNB {uint32_t tmpAddr = getTmpAddr(); fprintf(output_file, "6 %d %d ; Constante %d dans addresse temporaire %d\n", tmpAddr, $1, $1, tmpAddr);$$=tmpAddr;} ;
        | tAND tKEYWORD { 
            uint32_t ret = get_var($2); 
            fprintf(output_file, "; Recup de l'adresse (%d) de la variable %s\n",ret, $2); 
            $$ = ret; 
        }
        | tMUL tKEYWORD {
            uint32_t ptr_addr = get_var($2); 
            fprintf(output_file, "DEREF %d %d ",RESULT_MEM_ADDR,ptr_addr); // \n dans la ligne de commentaire après
            fprintf(output_file, ";Recup de la valeur à (%d) depuis le pointeur %s vers stockage des rés. (%d)\n",ptr_addr, $2,RESULT_MEM_ADDR); 
            
            $$ = RESULT_MEM_ADDR;

        }




FunctionDefinitions : FunctionDefinitions FuncDef 
                    |;

FuncDef : tINTVAR tKEYWORD {

            // d'abord on enregistre la fonction avec sa ligne de départ 
            add_func($2, ftell_line(output_file, ftell(output_file)),0);

        } tPO DeclArgs tPF {

            // l'intro de la fonction a été générée en même temps que les arguments

            // maintenant qu'on a le nombre d'arguments on peut le maj dans la table
            update_func_args($2,$4);


        } tACCO Body tACCF {
            // OUTRO
            // On dépile l'adresse de retour (stockée en premier) et on saute
            uint32_t tmpRet = getTmpAddr();
            fprintf("5 %d %d; (copie) Depile l'adr de retour vers une var temporaire\n",tmpRet,get_sp());
            pop_arg();
            fprintf(output_file, "7 %d ; saute sur l'adr de retour\n", tmpRet);
        };



// arguments of a function during its declaration 
DeclArgs : /* vide */ { $$ = 0; }
     | tINTVAR tKEYWORD { 
            // on crée la variable locale qui correspond à l'argument empilé
            uint32_t addr = add_var($2, 0, 0);

            $$ = 1; 

            fprintf("5 %d %d; (copie) Depile l'argument %d vers une var locale\n",addr,get_sp(),$$);
            pop_arg();
       }
     | tINTVAR tKEYWORD tVIRG DeclArgs { 
            add_var($2, 0, 0);
            $$ = 1 + $4; 
            fprintf("5 %d %d; (copie) Depile l'argument %d vers une var locale\n",addr,get_sp(),$$);
            pop_arg();
       };


// arguments of a function during its call
CallArgs : /* vide */ { $$ = 0; }
     | Expr { 
            // on crée la variable locale qui correspond à l'argument empilé
            $$ = 1; 
            fprintf("5 %d %d; (copie) Empile l'argument %d\n",get_sp(),$1,$$);
            push_arg();
       }
     | Expr tVIRG CallArgs { 
            $$ = 1 + $4; 
            fprintf("5 %d %d; (copie) Empile l'argument %d\n",get_sp(),$1,$$);
            push_arg();
       };

%%

