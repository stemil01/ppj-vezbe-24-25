CC = g++
CFLAGS = -Wall -Wextra

parser: lex.yy.o parser.tab.o sintaksno_stablo.o tabela_simbola.o
	$(CC) $(CFLAGS) $^ -o $@

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp sintaksno_stablo.hpp tabela_simbola.hpp
	bison --header $<

sintaksno_stablo.o: sintaksno_stablo.cpp sintaksno_stablo.hpp
	$(CC) $(CFLAGS) -c $< -o $@

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o parser.tab.* lex.yy.c parser
