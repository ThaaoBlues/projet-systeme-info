#include <stdlib.h>
#include <stdio.h>
#include "gestionMem.h"

int ftell_line(FILE* f,int current_pos){
    int c= EOF;
    int linecount=1;


    fflush(f);


    fseek(f,0,SEEK_SET);
    while (((c=fgetc(f)) != EOF) && ftell(f) <= current_pos) {
        
        if (c=='\n'){
            linecount++;
        }
            
    }

    // restore file pos
    fseek(f,current_pos,SEEK_SET);

    return linecount;

}
void fseek_line(FILE* f, int n){

    int c= EOF;
    int linecount=1;

    fflush(f);


    fseek(f,0,SEEK_SET);
    
    while (((c=fgetc(f)) != EOF) && (linecount < n)) {
        if (c=='\n')
            linecount++;
    }

    // get to first char of next line from file cursor position
    // as cursor is right after \n right now (next char), which is one position too far
    fseek(f,-1,SEEK_CUR);
}