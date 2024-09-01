FLEX=flex
CC=gcc

PROGRAMA = l7e1
LEXICO = LISTA_7_EXERCICIO_1.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c -o $(PROGRAMA)

clear:
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	