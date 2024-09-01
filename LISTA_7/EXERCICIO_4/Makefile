FLEX=flex
CC=gcc

PROGRAMA = cstats
LEXICO = LISTA_7_EXERCICIO_4.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c -o $(PROGRAMA)

clear:
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	