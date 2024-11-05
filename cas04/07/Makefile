lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: rimski_brojevi.l
	flex rimski_brojevi.l

.PHONY: clean
clean:
	rm lexer lex.yy.c
