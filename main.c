#include <stdlib.h>
#include <stdio.h>

void yyerror(char *s) { fprintf(stderr, "%s\n", s); }
int main(void) {
  printf("Perseur\n"); // yydebug=1;

  output_file = fopen("sortie.asm",'w');

  if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    printf("Début compil\n");

  yyparse();


  fclose(output_file);
    
    printf("Compilation terminée. Fichier 'sortie.asm' généré.\n");

    
  return 0;
}