%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
%}

%option noyywrap
%option yylineno

%%

"main" {printf("tMAIN\n"); return tMAIN;}
"const" {printf("tCONST\n"); return tCONST;}
"int" {printf("tINTVAR\n");return tINTVAR;}
"printf" {printf("tPRINTF\n");return tPRINTF;}
"if" {printf("tIF\n");return tIF;}
"else" {printf("tELSE\n");return tELSE;}
"while" {printf("tWhile\n");return tWHILE;}
"return" {printf("tRETURN\n"); return tRETURN;}

"*10^" {printf("tEXP\n");return tEXP;}
"="	{ printf("tEGAL\n");return tEGAL; }
"-"	{ printf("tSOU\n");return tSOU; }
"+"	{ printf("tADD\n");return tADD; }
"*"	{ printf("tMUL\n");return tMUL; }
"/"	{ printf("tDIV\n");return tDIV; }
"("	{ printf("tPO\n");return tPO; }
")"	{ printf("tPF\n");return tPF; }
"{"	{ printf("tACCO\n");return tACCO; }
"}"	{ printf("tACCF\n");return tACCF; }
"&" {printf("tAND\n"); return tAND;}
[0-9]+	{
	  yylval.nb = atoi(yytext);
	  printf("tNB\n");return tNB;
	}
[a-z|0-9|_]+	{
	if(strlen(yytext) > 4){
		return tERROR;
	}else{
	  strcpy(yylval.var,yytext);
	  printf("tKEYWORD=%s\n",yylval.var);return tKEYWORD;
	}

	}
[\t|' '|] {}
"," {printf("VIRGULE\n");return tVIRG;}
[\n] {printf("tENDLINE\n");}
";" {printf("tENDINST\n");return tENDINST;}
.	{ printf("tERROR\n"); return tERROR; }






