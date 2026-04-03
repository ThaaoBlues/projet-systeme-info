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
    Piste de réflexion:
    *p; decla pointeur
    *p = &i; => p poite sur i. C'est a dire que la valeur de p est l'addresse de i. Cela représente en assembleur : d'initialisé la valeur de p a l'addresse de i
    =====> au lieu de mov on affecte la valeur de l'addresse de i
    *p = 5 => i prend pour valeur 5
    
    J'ai fait une implementation ou c'est globalement comme une var sauf que a la place on utilise l'instruction d'affectation a la place de la copie. Cela permet d'avoir la valeur du pointeur renvoyer par expression. Pas sur de mon implem.

    
    




    // todo faire qu'on puisse acceder a la valeur dont pointe le pointeur et la modifier en conséquence
    // rajouter la & a la grammaire
    // Il faut rajouter les nouveau tokken dans tokken.h?
    