GRM=compilateur.y
LEX=compilateur.l
BIN=compilateur

CC=gcc
CFLAGS=-Wall -g

OBJ=y.tab.o lex.yy.o main.o

all: $(BIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@	

y.tab.c: $(GRM)
	yacc -d -Wcounterexamples -Wother $<

lex.yy.c: $(LEX)
	flex $<

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

flex :  $(OBJ)
	flex compilateur.l
	$(CC) flex_test.c $(CFLAGS) $^  -o flex_test
clean:
	rm $(OBJ) y.tab.c y.tab.h lex.yy.c

