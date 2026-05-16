%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int yylex();
#define NB_REGISTRES 16
typedef struct {
    int     mem_addr;    
    int     unstored;       // 1 = modifié depuis le dernier LOAD, doit être STORE
    int     last_used;   // pour LRU
} Registre;
Registre banc[NB_REGISTRES];
int      horloge_lru = 0; // compteur global d'accès
FILE *output_reg = NULL;
void init_banc() {
    for (int i = 0; i < NB_REGISTRES; i++) {
        banc[i].mem_addr  = -1;
        banc[i].unstored     =  0;
        banc[i].last_used =  0;
    }
}
// find if memory addr content is already cached or not
int find_reg(int mem_addr) {
    for (int i = 0; i < NB_REGISTRES; i++) {
        if (banc[i].mem_addr == mem_addr) {
            return i;
        }
    }
    return -1;
}
// choisis le registre à libérer
// LRU
int lru() {
    int victime = 0;
    for (int i = 1; i < NB_REGISTRES; i++) {
        if (banc[i].last_used < banc[victime].last_used) {
            victime = i;
        }
    }
    return victime;
}
int allouer_reg(int mem_addr) {
    // Cache HIT
    int r = find_reg(mem_addr);
    if (r != -1) {
        banc[r].last_used = ++horloge_lru;
        printf("[ALLOC] hit : %d contient déjà data_mem[%d]\n", r, mem_addr);
        return r;
    }
    // ============== CACHE MISS ==============
    // free register ?
    for (int i = 0; i < NB_REGISTRES; i++) {
        if (banc[i].mem_addr == -1) {
            // registre libre trouvé
            fprintf(output_reg, "0xA7%02x%02x00   ; chargement data_mem[%d] dans %d\n",
                    i, mem_addr, mem_addr, i);
            banc[i].mem_addr  = mem_addr;
            banc[i].unstored     = 0;
            banc[i].last_used = ++horloge_lru;
            printf("[ALLOC] libre : R%d <- data_mem[%d]\n", i, mem_addr);
            return i;
        }
    }
    // No free register ==> LRU Nuke :)
    int lru_reg = lru();
    // si unstored, on STORE avant d'écraser
    if (banc[lru_reg].unstored) {
        fprintf(output_reg, "0x38%02x%02x00   ; sauvegarde R%d (unstored) dans data_mem[%d]\n",
                banc[lru_reg].mem_addr, lru_reg, lru_reg, banc[lru_reg].mem_addr);
    } else {
        // already stored register's content, don't need to do anything
    }
    // Load content at new address into the register
    fprintf(output_reg, "0xA7%02x%02x00   ; chargement data_mem[%d] dans R%d ( après LRU)\n",
            lru_reg, mem_addr, mem_addr, lru_reg);
    banc[lru_reg].mem_addr = mem_addr;
    banc[lru_reg].unstored = 0;
    banc[lru_reg].last_used = ++horloge_lru;
    return lru_reg;
}
// Comme allouer registre mais sans LOAD comme on a le résultat en sortie d'ALU
int allouer_reg_dest(int mem_addr) {
    // réutilisation directe si déjà présent
    int r = find_reg(mem_addr);
    if (r != -1) {
        banc[r].unstored = 1;
        banc[r].last_used = ++horloge_lru;
        return r;
    }
    // registre libre ?
    for (int i = 0; i < NB_REGISTRES; i++) {
        if (banc[i].mem_addr == -1) {
            banc[i].mem_addr = mem_addr;
            banc[i].unstored = 1;
            banc[i].last_used = ++horloge_lru;
            return i;
        }
    }
    // LRU
    int lru_reg = lru();
    if (banc[lru_reg].unstored) {
        fprintf(output_reg, "0x38%02x%02x00   ; sauvegarde R%d (unstored) avant recyclage (LRU)\n",
                banc[lru_reg].mem_addr, lru_reg, lru_reg);
    }
    // chargement de la nouvelle valeur
    banc[lru_reg].mem_addr = mem_addr;
    banc[lru_reg].unstored = 1;
    banc[lru_reg].last_used = ++horloge_lru;
    return lru_reg;
}
// Force le STORE de tous les registres unstored.
// Appelé dans l'invaildation du banc
void store_unstored() {
    printf("[+] on store les registres unstored\n");
    for (int i = 0; i < NB_REGISTRES; i++) {
        if (banc[i].unstored && banc[i].mem_addr != -1) {
            fprintf(output_reg, "0x38%02x%02x00   ; store toutes les variables non stockées avant if ou appel de fct\n",
                    banc[i].mem_addr, i);
            banc[i].unstored = 0;
        }
    }
}
/*
Store le contenu et reset tous les registres.
Utile quand on branche/appel de fonction/fin de fonction ... 
*/
void invalider_banc() {
    store_unstored();
    for (int i = 0; i < NB_REGISTRES; i++) {
        banc[i].mem_addr = -1;
        banc[i].unstored = 0;
        banc[i].last_used = 0;
    }
}
void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "ERREUR CC : %s à la ligne %d\n", s, yylineno);
}
%}
%union { int nb; }
%token tADD tMUL tSOU tDIV tCOPY tAFC tJMP tJMF tPRINT tJMPREF tDEREF
%token <nb> tNB
%start S
%%
S : { init_banc(); } Instructions {
                store_unstored();
            };
Instructions
    : Instructions Instruction
    | // vide, fin de l'assembleur
    ;
    /*
 * le bit de poids fort signale l'utilisation du banc de registre pour stoquage de résultats
 * le second bit de poids fort signale l'utilisation de l'ALU
 * le troisieme bit de poids fort signale l'utilisation de la mémoire de données
 * le 4eme bit de de poids fort signale l'utilisation du banc de registre en lecture
 * +----------------+------+---------------------+-------------------+
 * |   Opération    | Code | Format d'instruction|    Description    |
 * |                |      |  OP   | A  | B  | C  |                   |
 * +----------------+------+-------+----+----+----+-------------------+
 * | Addition       | 0xD1 | ADD   | Ri | Rj | Rk | [Ri] <- [Rj] + [Rk]|
 * | Multiplication | 0xD2 | MUL   | Ri | Rj | Rk | [Ri] <- [Rj] * [Rk]|
 * | Soustraction   | 0xD3 | SOU   | Ri | Rj | Rk | [Ri] <- [Rj] - [Rk]|
 * | Division       | 0xD4 | DIV   | Ri | Rj | Rk | [Ri] <- [Rj] / [Rk]|
 * | Copie          | 0x95 | COP   | Ri | Rj | -- | [Ri] <- [Rj]       |
 * | Affectation    | 0x86 | AFC   | Ri | j  | -- | [Ri] <- j          |
 * | Chargement     | 0xA7 | LOAD  | Ri | @j | -- | [Ri] <- [@j]       |
 * | Sauvegarde     | 0x38 | STORE | @i | Rj | -- | [@i] <- [Rj]       |
 * | =========== INSTRUCTIONS RAJOUTEES ===============================
 * | Saut incond.   | 0x09 | JMP   |    |    | -- |                    
 * | Saut si false  | 0x0A | JMF   |    |    |    |
 * | charg. par drf | 0xAB | LOADR | Ri | Rj |    |
 * +----------------+------+-------+----+----+----+-------------------+
 */
Instruction :
    tADD tNB tNB tNB {
        int dst  = $2;
        int src1 = $3;
        int src2 = $4;
        int r1   = allouer_reg(src1);
        int r2   = allouer_reg(src2);
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg,
                "0xD1%02x%02x%02x ; data_mem[%d] = data_mem[%d] + data_mem[%d]\n",
                rdst, r1, r2, dst, src1, src2);
    }
    | tMUL tNB tNB tNB {
        int dst  = $2;
        int src1 = $3;
        int src2 = $4;
        int r1   = allouer_reg(src1);
        int r2   = allouer_reg(src2);
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg, "0xD2%02x%02x%02x   ; data_mem[%d] = data_mem[%d] * data_mem[%d]\n",
                rdst, r1, r2, dst, src1, src2);
    }
    | tSOU tNB tNB tNB {
        int dst  = $2;
        int src1 = $3;
        int src2 = $4;
        int r1   = allouer_reg(src1);
        int r2   = allouer_reg(src2);
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg, "0xD3%02x%02x%02x   ; data_mem[%d] = data_mem[%d] - data_mem[%d]\n",
                rdst, r1, r2, dst, src1, src2);
    }
    
    | tDIV tNB tNB tNB {
        int dst  = $2;
        int src1 = $3;
        int src2 = $4;
        int r1   = allouer_reg(src1);
        int r2   = allouer_reg(src2);
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg, "0xD4%02x%02x%02x   ; data_mem[%d] = data_mem[%d] / data_mem[%d]\n",
                rdst, r1, r2, dst, src1, src2);
    }
    | tCOPY tNB tNB {
        int dst = $2;
        int src = $3;
        int rsrc = allouer_reg(src);
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg, "0x95%02x%02x00 ; data_mem[%d] = data_mem[%d] (copie registre)\n",
                rdst, rsrc, dst, src);
    }
    | tAFC tNB tNB {
        int dst = $2;
        int cst = $3;
        int rdst = allouer_reg_dest(dst);
        fprintf(output_reg, "0x86%02x%02x00 ; R%d <- constante %d \n",
                rdst, cst, rdst, cst, dst);
    }
    | tJMP tNB {
        int addr = $2;
        store_unstored();      /* STORE les unstored avant le saut    */
        invalider_banc();   /* le code cible repart de zéro     */
        fprintf(output_reg, "0x09%02x0000 ; saut inconditionnel vers ligne %d\n",
                addr, addr);
    }
    | tJMF tNB tNB {
        int cond = $2;
        int addr = $3;
        int rcond = allouer_reg(cond);
        store_unstored();      /* STORE les unstored avant le saut    */
        invalider_banc();
        fprintf(output_reg, "0x0A%02x%02x00       ; si R%d (data_mem[%d]) == 0 (false) saute à %d\n",
                rcond, addr, rcond, cond, addr);
    }
    | tPRINT tNB {
        int addr = $2;
        int r    = allouer_reg(addr);
        fprintf(output_reg, "C %d ; print R%d (data_mem[%d])\n",
                r, r, addr);
    }
    // jump sur une addr contenu a une addr mémoire
    // utilisé pour les retour de fonction
    | tJMPREF tNB {
        int sp_addr = $2;
        // on charge l'adresse de retour depuis la pile
        int rret = allouer_reg(sp_addr);
        store_unstored();
        invalider_banc();
        fprintf(output_reg, "JMPR %d ; met l'addr à jump dans R%d (data_mem[%d]) et saute dessus\n",
                rret, rret, sp_addr);
    }
    | tDEREF tNB tNB {
        int dst     = $2;
        int ptr_reg = $3;
        int rptr  = allouer_reg(ptr_reg);  // registre qui contient l'adresse pointée
        int rdst  = allouer_reg_dest(dst);
        fprintf(output_reg, "0xAB%02x%02x00 ; deref : R%d <- data_mem[ R%d ] \n",
                rdst, rptr, rdst, rptr, ptr_reg);
    }
    ;
%%
int main(int argc, char **argv) {
    extern FILE *yyin;
    yyin = fopen("../compilation/sortie.asm", "r");
    if (!yyin) {
        perror("Impossible d'ouvrir sortie.asm");
        return 1;
    }
    output_reg = fopen("sortie_reg.asm", "w+");
    if (!output_reg) {
        perror("Impossible d'ouvrir sortie_reg.asm");
        fclose(yyin);
        return 1;
    }
    yyparse();
    fclose(yyin);
    fclose(output_reg);
    return 0;
}