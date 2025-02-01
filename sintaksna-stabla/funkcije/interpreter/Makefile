CC = g++
CFLAGS = -Wall -Wextra

parser: lex.yy.o parser.tab.o funkcija.o tabela_simbola.o
	$(CC) $(CFLAGS) $^ -o $@

lex.yy.o: lex.yy.c funkcija.hpp
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

parser.tab.o: parser.tab.cpp parser.tab.hpp funkcija.hpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header $<

funkcija.o: funkcija.cpp funkcija.hpp
	$(CC) $(CFLAGS) -c $< -o $@

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o parser lex.yy.c parser.tab.*
