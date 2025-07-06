CC = g++
CFLAGS = -Wall -Wextra

parser: lex.yy.o parser.tab.o tabela_simbola.o sintaksno_stablo.o
	$(CC) $(CFLAGS) $^ -o $@

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

parser.tab.o: parser.tab.cpp parser.tab.hpp tabela_simbola.o sintaksno_stablo.o
	$(CC) $(CFLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp tabela_simbola.hpp sintaksno_stablo.hpp
	bison --header $<

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

sintaksno_stablo.o: sintaksno_stablo.cpp sintaksno_stablo.hpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o parser lex.yy.* parser.tab.* 