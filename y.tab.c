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

#define VAR_NAME_SIZE 4
#define TAILLE_BANC_REGISTRES


typedef struct StackNode {
    int numero_ligne;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top; /* Pointeur vers le haut de la pile*/
} Stack;


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


void yyerror(char *s);
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 69 "compilateur.y"
typedef union YYSTYPE { int nb; char var[5]; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 100 "y.tab.c"

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
#define tERROR 265
#define tMAIN 266
#define tCONST 267
#define tINTVAR 268
#define tSEP 269
#define tENDLINE 270
#define tENDINST 271
#define tPRINTF 272
#define tEXP 273
#define tACCO 274
#define tACCF 275
#define tIF 276
#define tELSE 277
#define tWHILE 278
#define tNB 279
#define tID 280
#define tKEYWORD 281
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    8,    0,   10,   11,    9,    9,    9,   12,   12,   12,
   12,   12,   12,   13,   12,   14,   15,   16,   12,   17,
   12,    4,    4,    4,    4,    5,    5,    5,    5,    7,
    7,    7,    7,    6,    6,    6,    6,    1,    1,    1,
    1,    2,    2,    2,    3,    3,
};
static const YYINT yylen[] = {                            2,
    0,    7,    0,    0,    5,    2,    0,    4,    4,    3,
    2,    4,    3,    0,    4,    0,    0,    0,    8,    0,
    4,    3,    2,    3,    1,    3,    2,    3,    1,    3,
    2,    3,    1,    3,    2,    3,    1,    3,    3,    3,
    1,    3,    3,    1,    1,    1,
};
static const YYINT yydefred[] = {                         1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    3,
    0,    0,    0,    0,    0,    0,    0,   29,    0,    0,
    0,    0,   25,    0,   11,    0,   46,   45,    0,    0,
   44,    0,    0,    0,    0,    2,    6,    0,    0,   37,
    0,    0,    0,   27,   10,    0,    0,   33,    0,    0,
    0,   23,    0,    0,    0,   13,    0,    0,    4,    0,
    0,    0,    0,   28,    0,    0,   35,    8,   26,   24,
    0,    0,   31,    9,   22,   38,    0,    0,   43,   42,
    0,   15,   17,   21,   12,   36,   34,   32,   30,    5,
    0,   18,    0,   19,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  283,  291,  266,  258,  259,  274,  267,  268,  272,  274,
  276,  278,  281,  292,  295,  257,  263,  271,  281,  288,
  257,  263,  271,  281,  287,  258,  279,  281,  284,  285,
  286,  293,  284,  284,  257,  275,  292,  284,  257,  271,
  281,  289,  264,  288,  271,  284,  257,  271,  281,  290,
  264,  287,  284,  260,  261,  271,  262,  263,  292,  296,
  297,  300,  284,  271,  284,  264,  289,  271,  288,  271,
  284,  264,  290,  271,  287,  259,  285,  285,  286,  286,
  294,  292,  292,  292,  271,  271,  289,  271,  290,  275,
  298,  277,  299,  292,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          1,
   29,   30,   31,   25,   20,   42,   50,    2,   14,   32,
   81,   15,   60,   61,   91,   93,   62,
};
static const YYINT yysindex[] = {                         0,
    0, -261, -250, -208, -212, -109, -253, -248, -206,    0,
 -206, -206, -199, -209, -109, -206, -218,    0, -245, -189,
 -206, -217,    0, -237,    0, -206,    0,    0, -200, -249,
    0, -109, -239, -239, -206,    0,    0, -166, -206,    0,
 -233, -151, -216,    0,    0, -159, -206,    0, -222, -134,
 -214,    0, -163, -160, -160,    0, -160, -160,    0, -109,
 -109, -109, -143,    0,  -90, -218,    0,    0,    0,    0,
  -87, -217,    0,    0,    0,    0, -249, -249,    0,    0,
 -203,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -128,    0, -109,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0, -164,    0,    0,    0,    0,
    0,    0,    0,    0, -137,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -191,
    0, -164, -133, -121,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, -137,
 -127, -137,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -168, -145,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -137,    0,
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
    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
  -10,   34,   67,  -21,   31,  -34,    7,    0,  -15,    0,
    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 184
static const YYINT yytable[] = {                         37,
   33,   34,   52,   16,    3,   38,   67,    4,   21,   17,
   46,   16,   57,   58,   22,   53,   59,   18,   43,   21,
   54,   55,   23,   39,   63,   18,   51,   19,   65,   75,
   66,   87,   24,   23,   47,   19,   71,   40,   39,   47,
   16,   72,   21,   24,   82,   83,   84,   41,   48,   44,
    5,   26,   40,   48,   18,   73,   23,   35,   49,   54,
   55,    6,   41,   49,   19,   36,   24,   41,   41,   41,
   56,   90,   27,   69,   28,   41,   41,   94,   89,   41,
   41,   45,   41,   41,   41,   41,   41,   77,   78,   41,
   40,   40,   40,   54,   55,   76,   54,   55,   40,   40,
   54,   55,   40,   40,   64,   40,   40,   40,   40,   40,
    7,   70,   40,   39,   39,   39,   54,   55,   27,   68,
   28,   39,   39,   79,   80,   39,   39,   85,   39,   39,
   39,   39,   39,   14,   14,   39,   74,    7,   14,    7,
   14,   14,   14,   14,   14,   20,   20,   14,   92,    7,
   20,    0,   20,   20,   20,   20,   20,    7,    8,   20,
    0,    0,    9,    0,   10,    0,   11,    0,   12,   54,
   55,   13,   54,   55,    0,    0,    0,    0,    0,    0,
   86,    0,    0,   88,
};
static const YYINT yycheck[] = {                         15,
   11,   12,   24,  257,  266,   16,   41,  258,  257,  263,
   21,  257,  262,  263,  263,   26,   32,  271,  264,  257,
  260,  261,  271,  257,   35,  271,  264,  281,   39,   51,
  264,   66,  281,  271,  257,  281,   47,  271,  257,  257,
  257,  264,  257,  281,   60,   61,   62,  281,  271,   19,
  259,  258,  271,  271,  271,   49,  271,  257,  281,  260,
  261,  274,  281,  281,  281,  275,  281,  259,  260,  261,
  271,  275,  279,   43,  281,  267,  268,   93,   72,  271,
  272,  271,  274,  275,  276,  277,  278,   54,   55,  281,
  259,  260,  261,  260,  261,  259,  260,  261,  267,  268,
  260,  261,  271,  272,  271,  274,  275,  276,  277,  278,
  275,  271,  281,  259,  260,  261,  260,  261,  279,  271,
  281,  267,  268,   57,   58,  271,  272,  271,  274,  275,
  276,  277,  278,  267,  268,  281,  271,  275,  272,  277,
  274,  275,  276,  277,  278,  267,  268,  281,  277,  277,
  272,   -1,  274,  275,  276,  277,  278,  267,  268,  281,
   -1,   -1,  272,   -1,  274,   -1,  276,   -1,  278,  260,
  261,  281,  260,  261,   -1,   -1,   -1,   -1,   -1,   -1,
  271,   -1,   -1,  271,
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
   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 281
#define YYUNDFTOKEN 301
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
"tDIV","tMUL","tVIRG","tERROR","tMAIN","tCONST","tINTVAR","tSEP","tENDLINE",
"tENDINST","tPRINTF","tEXP","tACCO","tACCF","tIF","tELSE","tWHILE","tNB","tID",
"tKEYWORD","$accept","Main","Expr","DivMul","Terme","GroupedDecl",
"GroupedDeclConst","GroupedDeclConstPointeur","GroupedDeclPointeur","$$1",
"Body","$$2","$$3","Instruction","$$4","$$5","$$6","$$7","$$8","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : Main",
"$$1 :",
"Main : $$1 tMAIN tPO tPF tACCO Body tACCF",
"$$2 :",
"$$3 :",
"Body : tACCO $$2 Body $$3 tACCF",
"Body : Instruction Body",
"Body :",
"Instruction : tCONST tMUL GroupedDeclConstPointeur tENDINST",
"Instruction : tINTVAR tMUL GroupedDeclPointeur tENDINST",
"Instruction : tCONST GroupedDeclConst tENDINST",
"Instruction : tINTVAR GroupedDecl",
"Instruction : tKEYWORD tEGAL Expr tENDINST",
"Instruction : tPRINTF Expr tENDINST",
"$$4 :",
"Instruction : tIF Expr $$4 Body",
"$$5 :",
"$$6 :",
"$$7 :",
"Instruction : tIF Expr $$5 Body $$6 tELSE $$7 Body",
"$$8 :",
"Instruction : tWHILE Expr $$8 Body",
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
"Terme : tKEYWORD",
"Terme : tNB",

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
#line 211 "compilateur.y"

#line 520 "y.tab.c"

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
#line 79 "compilateur.y"
	{iniOutputFile();}
#line 1193 "y.tab.c"
break;
case 2:
#line 79 "compilateur.y"
	{printf("FNISHED MAIN BODY\n");printMem();fclose(output_file);}
#line 1198 "y.tab.c"
break;
case 3:
#line 82 "compilateur.y"
	{scopeDeeper();}
#line 1203 "y.tab.c"
break;
case 4:
#line 82 "compilateur.y"
	{scopeSmaller();free_scope();}
#line 1208 "y.tab.c"
break;
case 6:
#line 83 "compilateur.y"
	{}
#line 1213 "y.tab.c"
break;
case 7:
#line 84 "compilateur.y"
	{printf("body terminé, on remonte.\n");}
#line 1218 "y.tab.c"
break;
case 10:
#line 89 "compilateur.y"
	{printf("on déclare un/des constante");}
#line 1223 "y.tab.c"
break;
case 11:
#line 90 "compilateur.y"
	{printf("on a déclaré un/des nombre(s) entier(s)\n");}
#line 1228 "y.tab.c"
break;
case 12:
#line 91 "compilateur.y"
	{
        if(is_constante(yystack.l_mark[-3].var)){
            printf("ERREUR : IMPOSSIBLE DE CHANGER LA VALEUR DE LA CONSTANTE : %s\n",yystack.l_mark[-3].var);
        }else{
            uint32_t allocated_addr = get_var(yystack.l_mark[-3].var);
            fprintf(output_file, "5 %d %d ;Copie de %d dans %d\n",allocated_addr,yystack.l_mark[-1].nb,yystack.l_mark[-1].nb,allocated_addr);
        }
    }
#line 1240 "y.tab.c"
break;
case 13:
#line 99 "compilateur.y"
	{
        
        fprintf(output_file, "C %d ;PRINT de la valeur à l'addresse %d \n",yystack.l_mark[-1].nb,yystack.l_mark[-1].nb);
    }
#line 1248 "y.tab.c"
break;
case 14:
#line 106 "compilateur.y"
	{
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la position du if    */
        fprintf(output_file,";DebutIFl%d\n",ftell_line(output_file,ftell(output_file)));

    }
#line 1257 "y.tab.c"
break;
case 15:
#line 110 "compilateur.y"
	{
        int lineJump = ftell_line(output_file,ftell(output_file)); /* prend notre position*/
        printf("fin du body du IF detecté ligne %d\n",lineJump);
        fseek_line(output_file,pop(pile_lignes_a_finir)); /* revient sur le if pour jump neq à notre position*/
        fprintf(output_file,"8 %d %d; jump conditionnel vers ligne %d\n",yystack.l_mark[-2].nb,lineJump,lineJump); /* écris*/
        fseek(output_file,0,SEEK_END); /* reviens à la fin du fichier*/
    }
#line 1268 "y.tab.c"
break;
case 16:
#line 120 "compilateur.y"
	{
        fprintf(output_file,"; Debut IF %d avec ELSE\n",ftell_line(output_file,ftell(output_file)));
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la position du if*/
     }
#line 1276 "y.tab.c"
break;
case 17:
#line 123 "compilateur.y"
	{
        int lineJump = ftell_line(output_file,ftell(output_file))+1; /* prend notre ligne actuelle (fin de corps du if)*/
        fseek_line(output_file,pop(pile_lignes_a_finir)); /* saute à la ligne du debut du if*/
        fprintf(output_file,"8 %d %d ; jump conditionnel vers ligne %d\n",yystack.l_mark[-2].nb,lineJump,lineJump); /* écris de jump par dessus le body dans l'instruction if*/
        fseek(output_file,0,SEEK_END); /* reviens à la fin actuelle du fichier*/
    }
#line 1286 "y.tab.c"
break;
case 18:
#line 128 "compilateur.y"
	{
        fprintf(output_file,"; Debut Else %d\n",ftell_line(output_file,ftell(output_file))); 
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file))); /* stoque la ligne du début de body else*/
    }
#line 1294 "y.tab.c"
break;
case 19:
#line 131 "compilateur.y"
	{
        int lineJump = ftell_line(output_file,ftell(output_file))+1; /* prend notre ligne actuelle +1*/
        fseek_line(output_file,pop(pile_lignes_a_finir)); /* reviens au début du else*/
        fprintf(output_file,"7 %d\n",lineJump); /* écris de sauter par dessus le else (pour si on vient du if plus haut)*/
        fseek(output_file,0,SEEK_END); /* reviens à notre position d'écriture en fin de fichier*/
    }
#line 1304 "y.tab.c"
break;
case 20:
#line 149 "compilateur.y"
	{
        fprintf(output_file,";Debut WHILE %d",ftell_line(output_file,ftell(output_file)));
        push(pile_lignes_a_finir,ftell_line(output_file,ftell(output_file)));
    }
#line 1312 "y.tab.c"
break;
case 21:
#line 152 "compilateur.y"
	{
        int line_while = pop(pile_lignes_a_finir);
        fprintf(output_file,"7 %d \n",pile_lignes_a_finir); 
        int lineJump = ftell_line(output_file,ftell(output_file))+1;
        fseek_line(output_file,line_while);
        fprintf(output_file,"8 %d %d\n",yystack.l_mark[-2].nb,lineJump);
        fseek(output_file,0,SEEK_END);
    }
#line 1324 "y.tab.c"
break;
case 22:
#line 164 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1329 "y.tab.c"
break;
case 23:
#line 165 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,0); fprintf(output_file, "5 %d %d ;DECL VARIABLE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1334 "y.tab.c"
break;
case 24:
#line 166 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1339 "y.tab.c"
break;
case 25:
#line 167 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init variable) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1344 "y.tab.c"
break;
case 26:
#line 170 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,1); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1349 "y.tab.c"
break;
case 27:
#line 171 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,1); fprintf(output_file, "5 %d %d ;DECL CONSTANTE %s : (init par Copie de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1354 "y.tab.c"
break;
case 28:
#line 172 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1359 "y.tab.c"
break;
case 29:
#line 173 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1364 "y.tab.c"
break;
case 30:
#line 175 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,0); fprintf(output_file, "4 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1369 "y.tab.c"
break;
case 31:
#line 176 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,0); fprintf(output_file, "4 %d %d ;DECL Pointeur %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1374 "y.tab.c"
break;
case 32:
#line 177 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1379 "y.tab.c"
break;
case 33:
#line 178 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init Pointeur) Pointeur %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1384 "y.tab.c"
break;
case 34:
#line 180 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-2].var,1); fprintf(output_file, "4 %d %d ;DECL POINTEUR CONSTANTE %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-2].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1389 "y.tab.c"
break;
case 35:
#line 181 "compilateur.y"
	{uint32_t allocated_addr = add_var(yystack.l_mark[-1].var,1); fprintf(output_file, "4 %d %d ;DECL POINTEUR CONSTANT %s : (init par Affectation de %d dans %d)\n",allocated_addr,yystack.l_mark[0].nb,yystack.l_mark[-1].var,yystack.l_mark[0].nb,allocated_addr);yyval.nb = yystack.l_mark[0].nb;}
#line 1394 "y.tab.c"
break;
case 36:
#line 182 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1399 "y.tab.c"
break;
case 37:
#line 183 "compilateur.y"
	{fprintf(output_file,"6 %d %d ; (Init Pointeur CONSTANTE) Constante %d dans addresse de résulats \n",0,RESULT_MEM_ADDR,0,RESULT_MEM_ADDR);yyval.nb = RESULT_MEM_ADDR;}
#line 1404 "y.tab.c"
break;
case 38:
#line 187 "compilateur.y"
	{yyval.nb = yystack.l_mark[-1].nb;}
#line 1409 "y.tab.c"
break;
case 39:
#line 188 "compilateur.y"
	{
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "1 %d %d %d ; Addition \n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR;}
#line 1417 "y.tab.c"
break;
case 40:
#line 192 "compilateur.y"
	{ 
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "3 %d %d %d ; Soustraction \n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1425 "y.tab.c"
break;
case 41:
#line 196 "compilateur.y"
	{ yyval.nb = yystack.l_mark[0].nb;}
#line 1430 "y.tab.c"
break;
case 42:
#line 197 "compilateur.y"
	{
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "2 %d %d %d ; Multiplication\n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1438 "y.tab.c"
break;
case 43:
#line 201 "compilateur.y"
	{ 
            /* On écrit dans le fichier au lieu de la console*/
            fprintf(output_file, "4 %d %d %d ; Division\n", RESULT_MEM_ADDR, yystack.l_mark[-2].nb, yystack.l_mark[0].nb); 
            yyval.nb = RESULT_MEM_ADDR; }
#line 1446 "y.tab.c"
break;
case 44:
#line 205 "compilateur.y"
	{ yyval.nb = yystack.l_mark[0].nb;}
#line 1451 "y.tab.c"
break;
case 45:
#line 206 "compilateur.y"
	{ uint32_t ret = get_var(yystack.l_mark[0].var); fprintf(output_file, "; Addr %d est la variable %s\n",ret, yystack.l_mark[0].var); yyval.nb = ret; }
#line 1456 "y.tab.c"
break;
case 46:
#line 208 "compilateur.y"
	{uint32_t tmpAddr = getTmpAddr(); fprintf(output_file, "6 %d %d ; Constante %d dans addresse temporaire %d\n", tmpAddr, yystack.l_mark[0].nb, yystack.l_mark[0].nb, tmpAddr);yyval.nb=tmpAddr;}
#line 1461 "y.tab.c"
break;
#line 1463 "y.tab.c"
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
