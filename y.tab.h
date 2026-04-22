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
