0x86000300 ; R0 <- constante 3 
0x95010000 ; data_mem[4] = data_mem[3] (copie registre)
0x86020400 ; R2 <- constante 4 
0x86000400 ; R0 <- constante 4 
0xD1030200 ; data_mem[1] = data_mem[2] + data_mem[3]
0x95040300 ; data_mem[5] = data_mem[1] (copie registre)
0xD1030104 ; data_mem[1] = data_mem[4] + data_mem[5]
0x95050300 ; data_mem[6] = data_mem[1] (copie registre)
C 5 ; print R5 (data_mem[6])
0x38030000   ; store toutes les variables non stockées avant if ou appel de fct
0x38040100   ; store toutes les variables non stockées avant if ou appel de fct
0x38020200   ; store toutes les variables non stockées avant if ou appel de fct
0x38010300   ; store toutes les variables non stockées avant if ou appel de fct
0x38050400   ; store toutes les variables non stockées avant if ou appel de fct
0x38060500   ; store toutes les variables non stockées avant if ou appel de fct
