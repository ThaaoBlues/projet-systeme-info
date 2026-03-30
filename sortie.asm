6 3 5 ; Constante 5 dans addresse temporaire 3
5 4 3 ;DECL VARIABLE oui : (init par Copie de 3 dans 4)
5 5 3 ;DECL VARIABLE dog : (init par Copie de 3 dans 5)
5 6 3 ;DECL VARIABLE chat : (init par Copie de 3 dans 6)
; Addr 6 est la variable chat
; Addr 5 est la variable dog
1 1 6 5 ; Addition 
5 4 1 ;Copie de 1 dans 4
; Addr 4 est la variable oui
6 2 3 ; Constante 3 dans addresse temporaire 2
2 1 4 2 ; Multiplication
5 6 1 ;Copie de 1 dans 6
; Addr 6 est la variable chat
6 3 2 ; Constante 2 dans addresse temporaire 3
2 1 6 3 ; Multiplication
6 2 5 ; Constante 5 dans addresse temporaire 2
1 1 1 2 ; Addition 
; Addr 5 est la variable dog
3 1 1 5 ; Soustraction 
5 5 1 ;Copie de 1 dans 5
6 3 3 ; Constante 3 dans addresse temporaire 3
; Addr 5 est la variable dog
2 1 3 5 ; Multiplication
C 1 ;PRINT de la valeur à l'addresse 1 
