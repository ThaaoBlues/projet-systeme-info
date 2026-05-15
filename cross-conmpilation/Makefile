GRM=cc.y 
LEX=cc.l
BIN=cc

CC=gcc
CFLAGS=-Wall -g

OBJ=y.tab.o lex.yy.o

all: $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@	

y.tab.c y.tab.h: $(GRM) 
	yacc -d $<

lex.yy.c: $(LEX) y.tab.h
	flex $<

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	rm $(OBJ) y.tab.c y.tab.h lex.yy.c

