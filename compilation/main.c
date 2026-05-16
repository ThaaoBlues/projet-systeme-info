#include <stdlib.h>
#include <stdio.h>

int main(void) {
  printf("Perseur\n"); // yydebug=1;

  

    printf("Début compil\n");

  yyparse();

    
  printf("Compilation terminée. Fichier 'sortie.asm' généré.\n");

    
  return 0;
}