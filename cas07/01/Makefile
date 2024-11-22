CC = g++
CFLAGS = -Wall -Wextra

parser: parser.tab.o lex.yy.o kompleksan_broj.o
	$(CC) $(CFLAGS) $^ -o $@

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header $<

lex.yy.o: lex.yy.c parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

kompleksan_broj.o: kompleksan_broj.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o parser.tab.* parser lex.yy.c
