#include <stdlib.h>
#include <stdio.h>

void yyerror(char *s) { fprintf(stderr, "%s\n", s); }
int main(void) {
  printf("TEST LEXEUR\n"); // yydebug=1;
  yyparse();
  return 0;
}