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
    tERROR = 265,                  /* tERROR  */
    tMAIN = 266,                   /* tMAIN  */
    tCONST = 267,                  /* tCONST  */
    tINTVAR = 268,                 /* tINTVAR  */
    tSEP = 269,                    /* tSEP  */
    tENDLINE = 270,                /* tENDLINE  */
    tENDINST = 271,                /* tENDINST  */
    tPRINTF = 272,                 /* tPRINTF  */
    tEXP = 273,                    /* tEXP  */
    tACCO = 274,                   /* tACCO  */
    tACCF = 275,                   /* tACCF  */
    tNB = 276,                     /* tNB  */
    tID = 277,                     /* tID  */
    tKEYWORD = 278                 /* tKEYWORD  */
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
#define tNB 276
#define tID 277
#define tKEYWORD 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "compilateur.y"
 int nb; char var[5]; 

#line 116 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
