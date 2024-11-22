CC = g++
CFLAGS = -Wall -Wextra

parser: lex.yy.o parser.tab.o
	$(CC) $(CFLAGS) $^ -o $@

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header $<


.PHONY: clean

clean:
	rm parser.tab.cpp parser.tab.hpp parser lex.yy.c *.o
