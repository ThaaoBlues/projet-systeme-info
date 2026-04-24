;=====FONCTION : prou =====
5 4 4294967294; (copie) Depile l'argument 1 vers une var locale            
5 5 4294967293; (copie) Depile l'argument 2 vers une var locale                   
5 6 4294967292; (copie) Depile l'argument 3 vers une var locale                   
6 3 0 ; Constante 0 dans addresse temporaire 3
5 1 3 ; stoque la valeur renvoyée par la fonction dans l'addr de resultat
JMPREF 4294967294 ; saute sur l'adr de retour contenue dans la pile à l'adresse 4294967294 
;=====FIN DE FONCTION : prou =====
5 4294967295 16 ; (appel de fonction) on push l'adresse de retour          
6 3 1 ; Constante 1 dans addresse temporaire 3
6 2 101 ; Constante 101 dans addresse temporaire 2
6 3 5 ; Constante 5 dans addresse temporaire 3
5 4294967294 3; (copie) Empile l'argument 1
5 4294967293 2; (copie) Empile l'argument 2
5 4294967292 3; (copie) Empile l'argument 3
