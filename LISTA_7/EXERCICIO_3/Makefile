FLEX=flex
CC=gcc

PROGRAMA = l7e3
LEXICO = LISTA_7_EXERCICIO_3.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c -o $(PROGRAMA)

clear:
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	