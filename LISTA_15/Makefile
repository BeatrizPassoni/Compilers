FLEX=flex
BISON=bison
CC=gcc

PROGRAMA = l15e1
LEXICO = lexical.l
SINTATICO = syntactic.y

$(PROGRAMA): $(LEXICO) $(SINTATICO)
	$(FLEX) $(LEXICO)
	$(BISON) -d $(SINTATICO)
	$(CC) *.c -I. -o $(PROGRAMA)

clear:
	rm -f syntactic.tab.c
	rm -f syntactic.tab.h
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	rm saida.txt