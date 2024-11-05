lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: komentari.l
	flex komentari.l

.PHONY: clean
clean:
	rm lex.yy.c lexer