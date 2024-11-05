lexer: lex.yy.c
	gcc lex.yy.c -o lexer

lex.yy.c: lekser.l
	flex lekser.l

.PHONY: clean
clean:
	rm lexer lex.yy.c