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
	rm -f *.o playdom player *.gcov *.gcda *.gcno *.so *.out
	rm -f randomtestadventurer randomtestcard1 randomtestcard2
	rm -f unittest1 unittest2 unittest3 unittest4
	rm -f cardtest1 cardtest2 cardtest3 cardtest4
	rm -rf *.dSYM

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

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer.out: randomtestadventurer
	echo "Morgan Howard\nCS362 Assignment4\n" > randomtestadventurer.out
	echo "Random test results Adventurer\n" >> randomtestadventurer.out
	make randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out
	gcov -f dominion.c | grep -A 1 "card_adventurer" >> randomtestadventurer.out
	grep -A 44 "card_adventurer" dominion.c.gcov | head -43 >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	echo "Morgan Howard\nCS362 Assignment4\n" > randomtestcard1.out
	echo "Random test results for Smithy\n" >> randomtestcard1.out
	make randomtestcard1
	./randomtestcard1 >> randomtestcard1.out
	gcov -f dominion.c | grep -A 1 "card_smithy" >> randomtestcard1.out
	grep -A 16 "card_smithy" dominion.c.gcov | head -16 >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	echo "Morgan Howard\nCS362 Assignment4\n" > randomtestcard2.out
	echo "Random test results for Village\n" >> randomtestcard2.out
	make randomtestcard2
	./randomtestcard2 >> randomtestcard2.out
	gcov -f dominion.c | grep -A 1 "card_village" >> randomtestcard2.out
	grep -A 14 "card_village" dominion.c.gcov | head -14 >> randomtestcard2.out

randomtestresults.out: randomtestcard1.out randomtestcard2.out randomtestadventurer.out
	make randomtestcard1.out
	make randomtestcard2.out
	make randomtestadventurer.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "Morgan Howard\nCS362 Assignment3\n" > unittestresults.out
	echo "Unit test results\n" >> unittestresults.out
	make unittest1
	./unittest1 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "isGameOver" >> unittestresults.out
	touch dominion.c
	make unittest2 
	./unittest2 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "getCost" >> unittestresults.out
	# grep -A 61 "getCost(int" dominion.c.gcov | head -62 >> unittestresults.out
	touch dominion.c
	make unittest3
	./unittest3 >> unittestresults.out
	gcov -f dominion.c | grep -A 1 "endTurn" >> unittestresults.out
	# grep -A 40 "endTurn(struct" dominion.c.gcov | head -40 >> unittestresults.out
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
