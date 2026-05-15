%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap
%option yylineno


// L'idée d'utiliser des start symbol pour différentier 
// la zone où on parse les opcode et les la zone où on paarse les arguments
// car unn opcode peut avoir le même symbole qu'une adresse  ex : '4' pourrait être 
// l'opcode copy ou l'adresse 4 ou la constante 4

%x ARGS

%%



<INITIAL>";"[^\n]*\n          { /* commentaire seul, ignore */ }
<INITIAL>";"[^\n]*             { /* commentaire fin de ligne, ignore */ }
<INITIAL>[ \t]+                { /* espaces en debut de ligne */ }
<INITIAL>\n                    { /* ligne vide */ }

<INITIAL>"JMPREF"   { printf("[LEX] tJMPREF\n"); BEGIN(ARGS); return tJMPREF; }


<INITIAL>"C"        { printf("[LEX] tPRINT\n");  BEGIN(ARGS); return tPRINT;  }

<INITIAL>"1"        { printf("[LEX] tADD\n");    BEGIN(ARGS); return tADD;    }
<INITIAL>"2"        { printf("[LEX] tMUL\n");    BEGIN(ARGS); return tMUL;    }
<INITIAL>"3"        { printf("[LEX] tSOU\n");    BEGIN(ARGS); return tSOU;    }
<INITIAL>"4"        { printf("[LEX] tDIV\n");    BEGIN(ARGS); return tDIV;    }
<INITIAL>"5"        { printf("[LEX] tCOPY\n");   BEGIN(ARGS); return tCOPY;   }
<INITIAL>"6"        { printf("[LEX] tAFC\n");    BEGIN(ARGS); return tAFC;    }
<INITIAL>"7"        { printf("[LEX] tJMP\n");    BEGIN(ARGS); return tJMP;    }
<INITIAL>"8"        { printf("[LEX] tJMPF\n");   BEGIN(ARGS); return tJMF;   }

<ARGS>[0-9]+  {
    yylval.nb = atoi(yytext);
    printf("[LEX] tNB=%d\n", yylval.nb);
    return tNB;
}

<ARGS>";"[^\n]*\n  { BEGIN(INITIAL); }
<ARGS>";"[^\n]*     { }
<ARGS>\n            { BEGIN(INITIAL); }
<ARGS>[ \t]+        { }


%%
