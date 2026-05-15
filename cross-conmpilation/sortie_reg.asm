AFC R0 3 ; R0 <- constante 3 
COP R1 R0 ; data_mem[4] = data_mem[3] (copie registre)
AFC R2 4 ; R2 <- constante 4 
AFC R0 4 ; R0 <- constante 4 
ADD R3 R2 R0 ; data_mem[1] = data_mem[2] + data_mem[3]
COP R4 R3 ; data_mem[5] = data_mem[1] (copie registre)
ADD R3 R1 R4 ; data_mem[1] = data_mem[4] + data_mem[5]
COP R5 R3 ; data_mem[6] = data_mem[1] (copie registre)
C R5 ; print R5 (data_mem[6])
STORE data_mem[3] R0   ; store toutes les variables non stockées avant if ou appel de fct
STORE data_mem[4] R1   ; store toutes les variables non stockées avant if ou appel de fct
STORE data_mem[2] R2   ; store toutes les variables non stockées avant if ou appel de fct
STORE data_mem[1] R3   ; store toutes les variables non stockées avant if ou appel de fct
STORE data_mem[5] R4   ; store toutes les variables non stockées avant if ou appel de fct
STORE data_mem[6] R5   ; store toutes les variables non stockées avant if ou appel de fct
