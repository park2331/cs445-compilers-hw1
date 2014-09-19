CC=gcc
CFLAGS=-c -g

120++: 120++.o lex.yy.o token.o tlist.o 
	$(CC) -o 120++ 120++.o lex.yy.o token.o tlist.o

120++.o: 120++.c 
	$(CC) $(CFLAGS) 120++.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c

lex.yy.c: clex.l cgram.tab.h
	flex clex.l

token.o: token.c token.h
	$(CC) $(CFLAGS) token.c

tlist.o: tlist.c tlist.h
	$(CC) $(CFLAGS) tlist.c

## phase 2: ignore for now

#c: main.o cgram.tab.o lex.yy.o
#	cc -o c main.o cgram.tab.o lex.yy.o

#cgram.tab.o: cgram.tab.c
#	cc -c -DYYDEBUG cgram.tab.c

#cgram.tab.c: cgram.y
#	bison -d -v cgram.y

#cgram.tab.h: cgram.tab.c
