/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tEGAL = 258,                   /* tEGAL  */
    tPO = 259,                     /* tPO  */
    tPF = 260,                     /* tPF  */
    tSOU = 261,                    /* tSOU  */
    tADD = 262,                    /* tADD  */
    tDIV = 263,                    /* tDIV  */
    tMUL = 264,                    /* tMUL  */
    tVIRG = 265,                   /* tVIRG  */
    tAND = 266,                    /* tAND  */
    tERROR = 267,                  /* tERROR  */
    tMAIN = 268,                   /* tMAIN  */
    tCONST = 269,                  /* tCONST  */
    tINTVAR = 270,                 /* tINTVAR  */
    tSEP = 271,                    /* tSEP  */
    tENDLINE = 272,                /* tENDLINE  */
    tENDINST = 273,                /* tENDINST  */
    tPRINTF = 274,                 /* tPRINTF  */
    tEXP = 275,                    /* tEXP  */
    tACCO = 276,                   /* tACCO  */
    tACCF = 277,                   /* tACCF  */
    tIF = 278,                     /* tIF  */
    tELSE = 279,                   /* tELSE  */
    tWHILE = 280,                  /* tWHILE  */
    tRETURN = 281,                 /* tRETURN  */
    tNB = 282,                     /* tNB  */
    tID = 283,                     /* tID  */
    tKEYWORD = 284                 /* tKEYWORD  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define tEGAL 258
#define tPO 259
#define tPF 260
#define tSOU 261
#define tADD 262
#define tDIV 263
#define tMUL 264
#define tVIRG 265
#define tAND 266
#define tERROR 267
#define tMAIN 268
#define tCONST 269
#define tINTVAR 270
#define tSEP 271
#define tENDLINE 272
#define tENDINST 273
#define tPRINTF 274
#define tEXP 275
#define tACCO 276
#define tACCF 277
#define tIF 278
#define tELSE 279
#define tWHILE 280
#define tRETURN 281
#define tNB 282
#define tID 283
#define tKEYWORD 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 74 "compilateur.y"
 int nb; char var[5]; 

#line 128 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
