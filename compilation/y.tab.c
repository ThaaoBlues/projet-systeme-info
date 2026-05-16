/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20221106

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "compilateur.y"
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
    StackNode* top; /* Pointeur vers le haut de la pile*/
} Stack;

/*override de la fonction appeler par bison lors d'un tokken inatendu*/
void yyerror(const char *s) {
    extern int yylineno; /* On récupère la variable de Flex*/
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

    /* we found not extremely inapropriate to init stack here as well*/
    iniLineStack();

 	output_file = fopen("sortie.asm","w+");

  	if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
}


#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 74 "compilateur.y"
typedef union YYSTYPE { int nb; char var[5]; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 105 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tEGAL 257
#define tPO 258
#define tPF 259
#define tSOU 260
#define tADD 261
#define tDIV 262
#define tMUL 263
#define tVIRG 264
#define tAND 265
#define tERROR 266
#define tMAIN 267
#define tCONST 268
#define tINTVAR 269
#define tSEP 270
#define tENDLINE 271
#define tENDINST 272
#define tPRINTF 273
#define tEXP 274
#define tACCO 275
#define tACCF 276
#define tIF 277
#define tELSE 278
#define tWHILE 279
#define tRETURN 280
#define tNB 281
#define tID 282
#define tKEYWORD 283
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
   11,    0,   12,   14,   15,   13,   13,   13,   16,   17,
   16,   16,   16,   16,   16,   16,   16,   16,   16,   18,
   20,   16,   21,   16,   22,   19,   19,    4,    4,    4,
    4,    5,    5,    5,    5,    7,    7,    7,    7,    6,
    6,    6,    6,    1,    1,    1,    1,    2,    2,    2,
   23,    3,    3,    3,    3,    3,   10,   10,   25,   26,
   24,    8,    8,    8,    9,    9,   27,    9,
};
static const YYINT yylen[] = {                            2,
    0,    3,    6,    0,    0,    5,    2,    0,    0,    0,
    6,    3,    3,    3,    3,    2,    4,    3,    2,    0,
    0,    6,    0,    4,    0,    3,    0,    3,    2,    3,
    1,    3,    2,    3,    1,    3,    2,    3,    1,    3,
    2,    3,    1,    3,    3,    3,    1,    3,    3,    1,
    0,    5,    1,    1,    2,    2,    2,    0,    0,    0,
   10,    0,    2,    4,    0,    1,    0,    4,
};
static const YYINT yydefred[] = {                         1,
    0,   58,    0,    0,    0,    2,   57,    0,   59,    0,
    0,    0,    0,    0,    0,    0,    0,    4,    0,    0,
    0,    0,    0,    0,    0,    0,   19,    0,    0,   35,
    0,    0,    0,    0,   31,    0,   16,    0,    0,    0,
   54,    0,    0,    0,   50,    0,    0,    0,    0,    0,
   10,    3,    7,    0,   60,    0,    0,   43,    0,   13,
    0,   33,   15,    0,    0,   39,    0,   14,    0,   29,
    0,   56,   55,   51,    0,    0,   18,    0,    0,    5,
    0,    0,   12,    0,    0,    0,    0,   34,    0,    0,
   41,   32,   30,    0,    0,   37,   28,   44,    0,    0,
    0,   49,   48,    0,   21,   24,   17,    0,    0,   64,
    0,   42,   40,   38,   36,    0,    6,    0,    0,    0,
    0,   52,   25,   22,    0,   11,   61,    0,   68,   26,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  285,  296,  295,  267,  269,  297,  309,  258,  283,  259,
  310,  275,  258,  256,  268,  269,  273,  275,  277,  279,
  280,  283,  298,  301,  269,  293,  272,  257,  263,  272,
  283,  290,  257,  263,  272,  283,  289,  258,  263,  265,
  281,  283,  286,  287,  288,  299,  286,  286,  286,  257,
  258,  276,  298,  283,  259,  286,  257,  272,  283,  291,
  264,  290,  272,  286,  257,  272,  283,  292,  264,  289,
  286,  283,  283,  258,  260,  261,  272,  262,  263,  298,
  303,  306,  272,  286,  302,  264,  311,  272,  286,  264,
  291,  290,  272,  286,  264,  292,  289,  259,  308,  287,
  287,  288,  288,  300,  298,  298,  272,  286,  294,  293,
  275,  272,  291,  272,  292,  294,  276,  305,  312,  259,
  298,  259,  278,  304,  264,  272,  276,  307,  294,  298,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
  108,   44,   45,   37,   32,   60,   68,   26,  109,    3,
    2,    6,   23,   46,  104,   24,   85,   81,  124,  118,
   82,  128,   99,    7,   11,   87,  119,
};
static const YYINT yysindex[] = {                         0,
    0,    0, -162, -199, -271,    0,    0, -193,    0, -259,
 -170,  -67, -153, -173, -246, -243,  -43,    0,  -43,  -43,
  -43, -211, -147,  -67, -149, -104,    0,  -43, -242,    0,
  -69,  -97,  -43, -124,    0,  -53,    0,  -43, -100,  -92,
    0,  -51, -251, -238,    0,  -67, -152, -152, -233,  -43,
    0,    0,    0,  -65,    0, -229,  -43,    0,  -40,    0,
 -101,    0,    0, -198,  -43,    0,  -39,    0,  -85,    0,
 -177,    0,    0,    0,  -42,  -42,    0,  -42,  -42,    0,
  -67,  -67,    0, -181,  -43, -153,  -70,    0, -148, -242,
    0,    0,    0, -123, -124,    0,    0,    0,  -43, -238,
 -238,    0,    0,  -50,    0,    0,    0, -152,  -32,    0,
  -67,    0,    0,    0,    0,  -31,    0,  -49,  -55,  -41,
  -34,    0,    0,    0,  -43,    0,    0,  -67,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -30,  -25,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -146,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -208,    0, -183,    0,  -30, -115,  -99,    0,    0,
    0,    0,    0,  -23,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -146, -146,    0,    0,  -22,  -25,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -22, -158,
 -133,    0,    0,    0,    0,    0,    0, -215,    0,    0,
  -30,    0,    0,    0,    0,    0,    0,  -83,    0,    0,
    0,    0,    0,    0,  -22,    0,    0, -146,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
  -15,   76,   88,  -35,  -28,  -52,  -59,  149,  -80,    0,
    0,    0,  -24,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 246
static const YYINT yytable[] = {                         53,
   70,   43,   62,   47,   48,   49,   91,   96,   75,   76,
   28,    9,   56,   33,   57,   12,   29,   64,  116,   34,
   77,   80,   71,   78,   79,   30,   75,   76,   35,   58,
   75,   76,   92,   97,   84,  115,   31,  113,   83,   36,
   59,   89,   88,   66,  129,   50,   51,   53,   67,   94,
   53,   53,   53,   53,   53,   53,  105,  106,    8,   53,
   53,   75,   76,   53,   53,   10,   53,   53,   53,   53,
   53,   53,   47,   93,   53,   47,   47,   47,   75,   76,
   47,   98,   75,   76,   47,   47,  121,   13,   47,   47,
  107,   47,   47,   47,   47,   47,   47,   46,   27,   47,
   46,   46,   46,  130,    4,   46,    5,   75,   76,   46,
   46,   75,   76,   46,   46,   25,   46,   46,   46,   46,
   46,   46,   45,  112,   46,   45,   45,   45,   52,    8,
   45,    8,   65,   54,   45,   45,   75,   76,   45,   45,
   20,   45,   45,   45,   45,   45,   45,   66,  114,   45,
  100,  101,   20,   20,   55,   28,   23,   20,   67,   20,
   20,   20,   20,   20,   20,  102,  103,   20,   23,   23,
   30,   33,   27,   23,   63,   23,   23,   23,   23,   23,
   23,   31,   72,   23,   27,   27,   35,   28,   14,   27,
   73,   27,   27,   27,   61,   27,   27,   36,   86,   27,
   15,   16,   30,   33,  111,   17,   74,   18,  125,   19,
   69,   20,   21,   31,   38,   22,   57,   65,   35,   39,
   39,   40,   40,   90,   95,  117,  120,  122,  123,   36,
  126,   58,   66,   62,  110,   63,   65,   41,   41,   42,
   42,  127,   59,   67,    0,    8,
};
static const YYINT yycheck[] = {                         24,
   36,   17,   31,   19,   20,   21,   59,   67,  260,  261,
  257,  283,   28,  257,  257,  275,  263,   33,   99,  263,
  272,   46,   38,  262,  263,  272,  260,  261,  272,  272,
  260,  261,   61,   69,   50,   95,  283,   90,  272,  283,
  283,   57,  272,  259,  125,  257,  258,  256,  264,   65,
  259,  260,  261,  262,  263,  264,   81,   82,  258,  268,
  269,  260,  261,  272,  273,  259,  275,  276,  277,  278,
  279,  280,  256,  272,  283,  259,  260,  261,  260,  261,
  264,  259,  260,  261,  268,  269,  111,  258,  272,  273,
  272,  275,  276,  277,  278,  279,  280,  256,  272,  283,
  259,  260,  261,  128,  267,  264,  269,  260,  261,  268,
  269,  260,  261,  272,  273,  269,  275,  276,  277,  278,
  279,  280,  256,  272,  283,  259,  260,  261,  276,  276,
  264,  278,  257,  283,  268,  269,  260,  261,  272,  273,
  256,  275,  276,  277,  278,  279,  280,  272,  272,  283,
   75,   76,  268,  269,  259,  257,  256,  273,  283,  275,
  276,  277,  278,  279,  280,   78,   79,  283,  268,  269,
  272,  257,  256,  273,  272,  275,  276,  277,  278,  279,
  280,  283,  283,  283,  268,  269,  272,  257,  256,  273,
  283,  275,  276,  277,  264,  279,  280,  283,  264,  283,
  268,  269,  272,  257,  275,  273,  258,  275,  264,  277,
  264,  279,  280,  283,  258,  283,  257,  257,  272,  263,
  263,  265,  265,  264,  264,  276,  259,  259,  278,  283,
  272,  272,  272,  259,   86,  259,  259,  281,  281,  283,
  283,  276,  283,  283,   -1,  276,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYUNDFTOKEN 313
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","tEGAL","tPO","tPF","tSOU","tADD",
"tDIV","tMUL","tVIRG","tAND","tERROR","tMAIN","tCONST","tINTVAR","tSEP",
"tENDLINE","tENDINST","tPRINTF","tEXP","tACCO","tACCF","tIF","tELSE","tWHILE",
"tRETURN","tNB","tID","tKEYWORD","$accept","Start","Expr","DivMul","Terme",
"GroupedDecl","GroupedDeclConst","GroupedDeclConstPointeur",
"GroupedDeclPointeur","DeclArgs","CallArgs","FunctionDefinitions","$$1","Main",
"Body","$$2","$$3","Instruction","$$4","$$5","OptionalElse","$$6","$$7","$$8",
"$$9","FuncDef","$$10","$$11","$$12","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : Start",
"$$1 :",
"Start : $$1 FunctionDefinitions Main",
"Main : tMAIN tPO tPF tACCO Body tACCF",
"$$2 :",
"$$3 :",
"Body : tACCO $$2 Body $$3 tACCF",
"Body : Instruction Body",
"Body :",
"Instruction :",
"$$4 :",
"Instruction : tKEYWORD tPO $$4 CallArgs tPF tENDINST",
"Instruction : tRETURN Expr tENDINST",
"Instruction : tCONST tMUL GroupedDeclConstPointeur",
"Instruction : tINTVAR tMUL GroupedDeclPointeur",
"Instruction : tCONST GroupedDeclConst tENDINST",
"Instruction : tINTVAR GroupedDecl",
"Instruction : tKEYWORD tEGAL Expr tENDINST",
"Instruction : tPRINTF Expr tENDINST",
"Instruction : error tENDINST",
"$$5 :",
"$$6 :",
"Instruction : tIF Expr $$5 Body $$6 OptionalElse",
"$$7 :",
"Instruction : tWHILE Expr $$7 Body",
"$$8 :",
"OptionalElse : tELSE $$8 Body",
"OptionalElse :",
"GroupedDecl : tKEYWORD tVIRG GroupedDecl",
"GroupedDecl : tKEYWORD GroupedDecl",
"GroupedDecl : tEGAL Expr tENDINST",
"GroupedDecl : tENDINST",
"GroupedDeclConst : tKEYWORD tVIRG GroupedDeclConst",
"GroupedDeclConst : tKEYWORD GroupedDeclConst",
"GroupedDeclConst : tEGAL Expr tENDINST",
"GroupedDeclConst : tENDINST",
"GroupedDeclPointeur : tKEYWORD tVIRG GroupedDeclPointeur",
"GroupedDeclPointeur : tKEYWORD GroupedDeclPointeur",
"GroupedDeclPointeur : tEGAL Expr tENDINST",
"GroupedDeclPointeur : tENDINST",
"GroupedDeclConstPointeur : tKEYWORD tVIRG GroupedDeclConstPointeur",
"GroupedDeclConstPointeur : tKEYWORD GroupedDeclConstPointeur",
"GroupedDeclConstPointeur : tEGAL Expr tENDINST",
"GroupedDeclConstPointeur : tENDINST",
"Expr : tPO Expr tPF",
"Expr : Expr tADD DivMul",
"Expr : Expr tSOU DivMul",
"Expr : DivMul",
"DivMul : DivMul tMUL Terme",
"DivMul : DivMul tDIV Terme",
"DivMul : Terme",
"$$9 :",
"Terme : tKEYWORD tPO $$9 CallArgs tPF",
"Terme : tKEYWORD",
"Terme : tNB",
"Terme : tAND tKEYWORD",
"Terme : tMUL tKEYWORD",
"FunctionDefinitions : FunctionDefinitions FuncDef",
"FunctionDefinitions :",
"$$10 :",
"$$11 :",
"FuncDef : tINTVAR tKEYWORD $$10 tPO DeclArgs tPF $$11 tACCO Body tACCF",
"DeclArgs :",
"DeclArgs : tINTVAR tKEYWORD",
"DeclArgs : tINTVAR tKEYWORD tVIRG DeclArgs",
"CallArgs :",
"CallArgs : Expr",
"$$12 :",
"CallArgs : Expr $$12 tVIRG CallArgs",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 443 "compilateur.y"

#line 590 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 1:
#line 85 "compilateur.y"
	{iniOutputFile();}
#line 1263 "y.tab.c"
break;
case 2:
#line 85 "compilateur.y"
	{printf("FNISHED MAIN BODY\n");printMem();fclose(output_file);}
#line 1268 "y.tab.c"
break;
case 4:
#line 92 "compilateur.y"
	{scopeDeeper();}
#line 1273 "y.tab.c"
break;
case 5:
#line 92 "compilateur.y"
	{scopeSmaller();free_scope();}
#line 1278 "y.tab.c"
break;
case 7:
#line 93 "compilateur.y"
	{}
#line 1283 "y.tab.c"
break;
case 8:
#line 94 "compilateur.y"
	{printf("body terminé, on remonte.\n");}
#line 1288 "y.tab.c"
break;
case 10:
#line 98 "compilateur.y"
	{

        /* push l'adresse de retour avant les arguments*/

        /* PLACEHOLDER, les arguments peuvent être des expr*/
        /* on doit repasser après generation en ayant le bon offset*/
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file)));
        fprintf(output_file,"PLACEHOLDER appel;                                                         \n");
        push_arg();

    }
#line 1303 "y.tab.c"
break;
case 11:
#line 108 "compilateur.y"
	{ /* function call without value affectation*/
        
        
        uint32_t addr_ret = ftell_line(output_file,ftell(output_file));
        fseek_line(output_file,pop(pile_lignes_a_finir));


        /* on a push les arguments entre temps*/
        /* la place reservée pour l'adresse de retour*/
        /* est alors sp+nb_args+1*/
        uint32_t emplacement_pile = get_sp()+get_func_args(yystack.l_mark[-5].var)+1;
        fprintf(output_file, "5 %u %d ; (appel de fonction) on push l'adresse de retour",emplacement_pile,addr_ret);
        fseek(output_file,0,SEEK_END); /* reviens à la fin actuelle du fichier*/

        uint32_t line_jump = get_func(yystack.l_mark[-5].var);
        fprintf(output_file,"7 %d; saut debut fonction\n",line_jump); 

        /* simulation de pop des arguments par la fonction*/
        /* permet d'avoir sp à jour dans le code que l'on génère*/
        for(int i =0; i< get_func_args(yystack.l_mark[-5].var);i++){
            pop_arg();
        }

    }
#line 1331 "y.tab.c"
break;
case 12:
#line 133 "compilateur.y"
	{

        fprintf(output_file,"5 %d %d ; stoque la valeur renvoyée par la fonction dans l'addr de resultat\n",RESULT_MEM_ADDR,yystack.l_mark[-1].nb);

    }
#line 1340 "y.tab.c"
break;
case 15:
#line 140 "compilateur.y"
	{printf("on déclare un/des constante");}
#line 1345 "y.tab.c"
break;
case 16:
#line 141 "compilateur.y"
	{printf("on a déclaré un/des nombre(s) entier(s)\n");}
#line 1350 "y.tab.c"
break;
case 17:
#line 142 "compilateur.y"
	{
        if(is_constante(yystack.l_mark[-3].var)){
            printf("ERREUR : IMPOSSIBLE DE CHANGER LA VALEUR DE LA CONSTANTE : %s\n",yystack.l_mark[-3].var);
        
        /* suivi des pointeurs (necessaire car leur valeur doit être connue à la compilation)*/
        }else if (is_pointeur(yystack.l_mark[-3].var)) {
            uint32_t allocated_addr = get_var(yystack.l_mark[-3].var);
            fprintf(output_file, "5 %d %d ;Copie de %d dans le pointeur stocké à l'adresse %d\n",allocated_addr,yystack.l_mark[-1].nb,yystack.l_mark[-1].nb,allocated_addr);
        }else{
            uint32_t allocated_addr = get_var(yystack.l_mark[-3].var);
            fprintf(output_file, "5 %d %d ;Copie de %d dans la variable stockée à l'adresse %d\n",allocated_addr,yystack.l_mark[-1].nb,yystack.l_mark[-1].nb,allocated_addr);

        }
    }
#line 1368 "y.tab.c"
break;
case 18:
#line 156 "compilateur.y"
	{
        
        fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",yystack.l_mark[-1].nb,yystack.l_mark[-1].nb);
    }
#line 1376 "y.tab.c"
break;
case 19:
#line 160 "compilateur.y"
	{ 
        yyerrok; /*empeche bison de crash et continuer la compilation pour voir les autre erreur*/
        printf("Récupération de l'erreur effectuée. On continue l'analyse! \n");
    }
#line 1384 "y.tab.c"
break;
case 20:
#line 167 "compilateur.y"
	{
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la position du if*/
        fprintf(output_file,"; Debut IF ligne %d avec ELSE                             \n",ftell_line(output_file,ftell(output_file)));
 
    }
#line 1393 "y.tab.c"
break;
case 21:
#line 171 "compilateur.y"
	{
        /* prend notre ligne actuelle (fin de corps du if)*/
        /* +2 pour sauter le jump de else */
        int lineJump = ftell_line(output_file,ftell(output_file))+2;
        fseek_line(output_file,pop(pile_lignes_a_finir)); /* saute à la ligne du debut du if*/
        fprintf(output_file,"8 %d %d ; jump conditionnel vers ligne %d\n",yystack.l_mark[-2].nb,lineJump,lineJump); /* écris de jump par dessus le body dans l'instruction if*/
        fseek(output_file,0,SEEK_END); /* reviens à la fin actuelle du fichier*/
    }
#line 1405 "y.tab.c"
break;
case 22:
#line 178 "compilateur.y"
	{}
#line 1410 "y.tab.c"
break;
case 23:
#line 182 "compilateur.y"
	{
        int line_while_start = ftell_line(output_file,ftell(output_file));
        push(pile_lignes_a_finir,line_while_start);
        fprintf(output_file,";Debut WHILE %d                                             \n",line_while_start);
    }
#line 1419 "y.tab.c"
break;
case 24:
#line 186 "compilateur.y"
	{
        int line_while = pop(pile_lignes_a_finir);
        fprintf(output_file,"7 %d; saut inconditionel pour remonter à la condition du while\n",line_while); 
        int lineJump = ftell_line(output_file,ftell(output_file))+1;
        fseek_line(output_file,line_while);
        fprintf(output_file,"8 %d %d; condition du while\n",yystack.l_mark[-2].nb,lineJump);
        fseek(output_file,0,SEEK_END);
    }
#line 1431 "y.tab.c"
break;
case 25:
#line 200 "compilateur.y"
	{
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la ligne du début de body else*/
        fprintf(output_file,"; Debut Else ligne %d                                                               \n",ftell_line(output_file,ftell(output_file))); 

    }
#line 1440 "y.tab.c"
break;
case 26:
#line 204 "compilateur.y"
	{
        int lineJump = ftell_line(output_file,ftell(output_file)); /* prend notre ligne actuelle*/
        fseek_line(output_file,pop(pile_lignes_a_finir)); /* reviens au début du else*/
        fprintf(output_file,"7 %d ; saut inconditionnel vers la ligne %d pour éviter le else",lineJump,lineJump); /* écris de sauter par dessus le else (pour si on vient du if plus haut)*/
        fseek(output_file,0,SEEK_END); /* reviens à notre position d'écriture en fin de fichier*/
    }
#line 1450 "y.tab.c"
break;
case 27:
#line 211 "compilateur.y"
	{
        int lineJump = ftell_line(output_file,ftell(output_file))+1;
        fprintf(output_file,"7 %d ; saut inconditionnel qui sert à rien pour avoir un offset de saut constant\n",lineJump,lineJump);}
#line 1457 "y.tab.c"
break;
case 28:
#line 219 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,0,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1462 "y.tab.c"
break;
case 29:
#line 220 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,0,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1467 "y.tab.c"
break;
case 30:
#line 221 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1472 "y.tab.c"
break;
case 31:
#line 222 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init variable) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1477 "y.tab.c"
break;
case 32:
#line 225 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,1,0); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1482 "y.tab.c"
break;
case 33:
#line 226 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,1,0); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1487 "y.tab.c"
break;
case 34:
#line 227 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1492 "y.tab.c"
break;
case 35:
#line 228 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1497 "y.tab.c"
break;
case 36:
#line 231 "compilateur.y"
	{
        uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,0,1); 
        fprintf(output_file, "5 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);
        yyval.nb = yystack.l_mark[0].nb;
    }
#line 1506 "y.tab.c"
break;
case 37:
#line 236 "compilateur.y"
	{
        uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,0,1); 
        fprintf(output_file, "5 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);
        yyval.nb = yystack.l_mark[0].nb;
    }
#line 1515 "y.tab.c"
break;
case 38:
#line 242 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1520 "y.tab.c"
break;
case 39:
#line 244 "compilateur.y"
	{
        fprintf(output_file,"6 %d %d ; (Init Pointeur) Pointeur %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);
        yyval.nb = RESULT_MEM_ADDR;
    }
#line 1528 "y.tab.c"
break;
case 40:
#line 251 "compilateur.y"
	{
    uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,1,1); 
    fprintf(output_file, "5 %d %d ;DECL POINTEUR CONSTANTE %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);
    yyval.nb = yystack.l_mark[0].nb;
    }
#line 1537 "y.tab.c"
break;
case 41:
#line 256 "compilateur.y"
	{
        uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,1,1); 
        fprintf(output_file, "5 %d %d ;DECL POINTEUR CONSTANT %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);
        yyval.nb = yystack.l_mark[0].nb;
    }
#line 1546 "y.tab.c"
break;
case 42:
#line 261 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1551 "y.tab.c"
break;
case 43:
#line 262 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init Pointeur CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1556 "y.tab.c"
break;
case 44:
#line 266 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1561 "y.tab.c"
break;
case 45:
#line 267 "compilateur.y"
	{
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "1 %d %d %d ; Addition \n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR;}
#line 1569 "y.tab.c"
break;
case 46:
#line 271 "compilateur.y"
	{ 
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "3 %d %d %d ; Soustraction \n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1577 "y.tab.c"
break;
case 47:
#line 275 "compilateur.y"
	{ yyval.nb = yystack.l_mark[0].nb;}
#line 1582 "y.tab.c"
break;
case 48:
#line 278 "compilateur.y"
	{
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "2 %d %d %d ; Multiplication\n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1590 "y.tab.c"
break;
case 49:
#line 282 "compilateur.y"
	{ 
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "4 %d %d %d ; Division\n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1598 "y.tab.c"
break;
case 50:
#line 286 "compilateur.y"
	{ yyval.nb = yystack.l_mark[0].nb;}
#line 1603 "y.tab.c"
break;
case 51:
#line 289 "compilateur.y"
	{

        /* push l'adresse de retour avant les arguments*/

        /* PLACEHOLDER, les arguments peuvent être des expr*/
        /* on doit repasser après generation en ayant le bon offset*/
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file)));
        fprintf(output_file,"PLACEHOLDER appel;                                                             \n");
        push_arg();

        }
#line 1618 "y.tab.c"
break;
case 52:
#line 299 "compilateur.y"
	{ /* function call without value affectation*/
            
            uint32_t addr_ret = ftell_line(output_file,ftell(output_file));
            fseek_line(output_file,pop(pile_lignes_a_finir));

            /* on a push les arguments entre temps*/
            /* la place reservée pour l'adresse de retour*/
            /* est alors sp+nb_args+1*/
            uint32_t emplacement_pile = get_sp()+get_func_args(yystack.l_mark[-4].var)+1;
            fprintf(output_file, "5 %u %d ; (appel de fonction) on push l'adresse de retour",emplacement_pile,addr_ret);
            fseek(output_file,0,SEEK_END); /* reviens à la fin actuelle du fichier*/

            uint32_t line_jump = get_func(yystack.l_mark[-4].var);
            fprintf(output_file,"7 %d; saut debut fontion\n",line_jump);

            /* le resultat d'evaluation la fonction est toujours contenu dans RESULT_MEM_ADDR*/
            yyval.nb = RESULT_MEM_ADDR;
        }
#line 1640 "y.tab.c"
break;
case 53:
#line 318 "compilateur.y"
	{ /* variable */
            uint32_t ret = get_var(yystack.l_mark[0].var); 
            fprintf(output_file, "; Addr %d est la variable %s\n",ret, yystack.l_mark[0].var); 
            yyval.nb = ret; 
        }
#line 1649 "y.tab.c"
break;
case 54:
#line 324 "compilateur.y"
	{
            uint32_t tmpAddr = getTmpAddr(); 
            fprintf(output_file, "6 %d %d ; Constante %d dans addresse temporaire %d\n", tmpAddr, yystack.l_mark[0].nb, yystack.l_mark[0].nb, tmpAddr);
            yyval.nb=tmpAddr;
        }
#line 1658 "y.tab.c"
break;
case 55:
#line 329 "compilateur.y"
	{ 
            uint32_t ret = get_var(yystack.l_mark[0].var); 
            fprintf(output_file, "; Recup de l'adresse (%d) de la variable %s\n",ret, yystack.l_mark[0].var); 
            yyval.nb = ret; 
        }
#line 1667 "y.tab.c"
break;
case 56:
#line 334 "compilateur.y"
	{
            uint32_t ptr_addr = get_var(yystack.l_mark[0].var); 
            fprintf(output_file, "DEREF %d %d ",RESULT_MEM_ADDR,ptr_addr); /* \n dans la ligne de commentaire après*/
            fprintf(output_file, ";Recup de la valeur à (%d) depuis le pointeur %s vers stockage des rés. (%d)\n",ptr_addr, yystack.l_mark[0].var,RESULT_MEM_ADDR); 
            
            yyval.nb = RESULT_MEM_ADDR;

        }
#line 1679 "y.tab.c"
break;
case 59:
#line 352 "compilateur.y"
	{


            fprintf(output_file,";=====FONCTION : %s =====\n",yystack.l_mark[0].var);
            /* d'abord on enregistre la fonction avec sa ligne de départ */
            add_func(yystack.l_mark[0].var, ftell_line(output_file, ftell(output_file)),0);
            
            /* offset pour prendre en compte le fait*/
            /* quer l'addr de retour sera deja sur la pile*/
            push_arg();
        }
#line 1694 "y.tab.c"
break;
case 60:
#line 362 "compilateur.y"
	{

            /* l'intro de la fonction a été générée en même temps que les arguments*/

            /* maintenant qu'on a le nombre d'arguments on peut le maj dans la table*/
            update_func_args(yystack.l_mark[-4].var,yystack.l_mark[-1].nb);
            
            /* simule les arguments empilés avant l'appel de fonction*/
            /* pour avoir les bonnes valeurs de sp*/
            /*printf("La fonction déclarée a %d arguments\n",$<nb>5);*/
            for(int i = 0; i<yystack.l_mark[-1].nb; i++){
                push_arg();
            }


            /* on dépile dans des vars locales*/
            /* comme on vient de les créer*/
            /* leurs adresses sont les dernières*/
            uint32_t var_addr = get_next_free_addr()-1;
            for(int i = yystack.l_mark[-1].nb; i > 0; i--){
                uint32_t ligne = pop(pile_lignes_a_finir);
                printf("itération %d, modif ligne %u\n",i,ligne);
                fseek_line(output_file,ligne);

                /* pas de saut de ligne, on l'a mis dans le placeholder !*/
                fprintf(output_file, "5 %d %u; (copie) Depile l'argument %d vers une var locale",var_addr,get_sp()+1,i);
                var_addr--;
                pop_arg();
                fseek(output_file,0,SEEK_END);

            }


        }
#line 1732 "y.tab.c"
break;
case 61:
#line 395 "compilateur.y"
	{
            /* OUTRO*/
            /* On dépile l'adresse de retour (stockée en premier) et on saute*/
            uint32_t tmpRet = getTmpAddr();
            
            /*fprintf(output_file, "5 %d %u; (copie) Depile l'adr de retour vers une var temporaire\n",tmpRet,);*/
            fprintf(output_file, "JMPREF %u ; saute sur l'adr de retour contenue dans la pile à l'adresse %u \n", get_sp(), get_sp());
            pop_arg();
            fprintf(output_file,";=====FIN DE FONCTION : %s =====\n",yystack.l_mark[-8].var);

        }
#line 1747 "y.tab.c"
break;
case 62:
#line 410 "compilateur.y"
	{ yyval.nb = 0; }
#line 1752 "y.tab.c"
break;
case 63:
#line 411 "compilateur.y"
	{ 
            /* on crée la variable locale qui correspond à l'argument empilé*/
            uint32_t var_addr = add_var(yystack.l_mark[0].var, 0, 0);

            yyval.nb = 1; 
            push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la ligne du début de body else*/
            fprintf(output_file, "POP arg placeholder;                                                       \n");

        }
#line 1765 "y.tab.c"
break;
case 64:
#line 420 "compilateur.y"
	{ 
            uint32_t var_addr = add_var(yystack.l_mark[-2].var, 0, 0);
            yyval.nb = 1 + yystack.l_mark[0].nb; 
            push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la ligne du début de body else*/
            fprintf(output_file, "POP arg placeholder;                                                              \n");
        }
#line 1775 "y.tab.c"
break;
case 65:
#line 429 "compilateur.y"
	{ yyval.nb = 0; }
#line 1780 "y.tab.c"
break;
case 66:
#line 430 "compilateur.y"
	{ 
            /* on crée la variable locale qui correspond à l'argument empilé*/
            yyval.nb = 1; 
            fprintf(output_file, "5 %u %d; (copie) Empile l'argument 1\n",get_sp(),yystack.l_mark[0].nb,yyval.nb);
            push_arg();
       }
#line 1790 "y.tab.c"
break;
case 67:
#line 436 "compilateur.y"
	{ 
             
            fprintf(output_file, "5 %u %d; (copie) Empile un argument\n",get_sp(),yystack.l_mark[0].nb);
            push_arg();
       }
#line 1799 "y.tab.c"
break;
case 68:
#line 440 "compilateur.y"
	{yyval.nb = 1 + yystack.l_mark[-1].nb;}
#line 1804 "y.tab.c"
break;
#line 1806 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
