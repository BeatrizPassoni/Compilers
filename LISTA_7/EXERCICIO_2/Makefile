FLEX=flex
CC=gcc

PROGRAMA = l7e2
LEXICO = LISTA_7_EXERCICIO_2.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c -o $(PROGRAMA)

clear:
	rm -f lex.yy.c
	rm -f $(PROGRAMA)
	