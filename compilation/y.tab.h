#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE { int nb; char var[5]; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
