# projet-systeme-info


MODIF bastien:

J'ai pas pu tester mes modifs donc faut tester :
Constante : 
    - tester de changer la valeur d'un int => ne doit pas afficher de message d'erreur
    - tester de changer la valeur d'un const => doit afficher une erreur dans le terminal de compilation

If else : 
    J'ai implémenter le else MAIS il faut regler le probleme de fseek et trouver une fonction qui donne la ligne du fichier. Détail de l'implém en commentaire dans le yacc du if else
    -tester avec les ligne dans exemple_ligne

While : 
    Implémentation du while. Similaire a un if, plus de détail sur l'implém en commentaire du yacc.
    De la même manière que le if else, il faut changer fseek pour fonciton qui donne ligne du fichier
    -tester avec les ligne dans exemple_ligne


Pointeur:

VHDL todo :

finir alu modification avec CRTL_alu
finir de faire le carry pour tout les flags
faire flag overflow et autre
verif avec test

COMPILATEUR TODO :
- tester le while et if/else
- tester les pointeurs
- pour les fonctions : 
    * dépiler les arguments en intro du code de la fonction
    * empiler les args et l'addr de retour avant chaque appel de la fonction
    * mettre le resultat dans l'addr globale de resultat  en outro de la fonction
    * depiler l'addr de retour et sauter dessus en outro de la fonction 


- Implémentation de fonctions 
Vous allez rajouter l'implémentation de fonctions en langage C. Vous allez faire les
modifications nécessaires au niveau de l’analyseur lexical et syntaxique de votre
compilateur. Vous allez également rajouter les instructions assembleur nécessaires pour
l'implémentation de fonctions.


- Traitement des erreurs
Dans un premier temps, un traitement des erreurs simple est à implémenter au niveau
du compilateur. Il permettra de détecter qu’une erreur est intervenue, d’afficher un message
d’erreur et la ligne sur laquelle l’erreur se trouve dans un premier temps.
Dans un second temps il faut pouvoir analyser une erreur pour ensuite continuer
l’analyse de la chaîne d’entrée.

Gestion d'erreur DONE: on peut écirer son fichier en entier et le compilateur indique chaque ligne ayant une faute.
TODO ? indiqué quel type d'erreur? complexe car il faut gerer tout les erreur imaginable