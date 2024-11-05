lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: html_ispis.l
	flex html_ispis.l

.PHONY: clean
clean:
	rm lex.yy.c lexer