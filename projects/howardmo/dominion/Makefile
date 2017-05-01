CFLAGS = -Wall -fpic -std=c99 -ftest-coverage -fprofile-arcs -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o interface.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o interface.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o interface.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Unit test results\n" > unittestresults.out
	make unittest1
	./unittest1 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "isGameOver" >> unittestresults.out
	touch dominion.c
	make unittest2 
	./unittest2 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "getCost" >> unittestresults.out
	grep -A 61 "getCost(int" dominion.c.gcov | head -62 >> unittestresults.out
	touch dominion.c
	make unittest3
	./unittest3 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "endTurn" >> unittestresults.out
	grep -A 40 "endTurn(struct" dominion.c.gcov | head -40 >> unittestresults.out
	touch dominion.c
	make unittest4
	./unittest4 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "buyCard" >> unittestresults.out
	touch dominion.c
	echo "\n\nCard test results" >> unittestresults.out
	make cardtest1
	./cardtest1 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "card_smithy" >> unittestresults.out
	touch dominion.c
	make cardtest2
	./cardtest2 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "card_adventurer" >> unittestresults.out
	grep -A 42 "card_adventurer" dominion.c.gcov | head -43 >> unittestresults.out
	touch dominion.c
	make cardtest3
	./cardtest3 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "card_village" >> unittestresults.out
	touch dominion.c
	make cardtest4
	./cardtest4 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "card_great_hall" >> unittestresults.out