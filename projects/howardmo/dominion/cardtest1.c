/*
Created by Morgan Howard on 4/23/17.
Test Smithy card
+3 cards

Card requirements:
A. player should draw 3 cards (e.g. +3 in hand, -3 in deck)
B. no state change for other players
C. no state change to victory and kingdom card piles

> make clean; make cardtest1; cardtest1
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

// bash-style return vals, 0 = true, 1 = false
// noise values:
// 0 - print both
// 1 - print only fail
int assertTrue(int value1, int value2, int noise)
{
    int assert_result = -1;
    if (value1 == value2)
    {
        if (noise == 0)
        {
            printf("PASS\n");
        }
        assert_result = 0;
    }
    else
    {
        printf("FAIL %d %d\n", value1, value2);
        assert_result = 1;
    }
    return assert_result;
}

int main()
{
    printf("-------- cardtest1 --------\n");
    // init game state
    struct gameState G, testG;
    int assert_value, i, result;
    int seed = 100;
    int numPlayers = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10] = {adventurer,
                 gardens,
                 embargo,
                 village,
                 minion,
                 mine,
                 cutpurse,
                 sea_hag,
                 tribute,
                 smithy
    };

    initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("\n*** Test A started ***\n");
    assert_value = 0;
    // play card
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    // this caught the bug i introduced for assignment 2; smithy drawing 4 cards intstead of 3
    result = assertTrue(G.deckCount[0] - 3, testG.deckCount[0], 1);
    assert_value += result;

    // this also caught the same bug caught above; smithy is drawing 4 cards instead of 3
    // hand should have +3 cards from the draw and -1 from discarding smithy
    result = assertTrue(G.handCount[0] + 3 - 1, testG.handCount[0], 1);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test A finished ***\n");

    printf("\n*** Test B started ***\n");
    assert_value = 0;
    result = assertTrue(G.deckCount[1], testG.deckCount[1], 1);
    assert_value += result;

    result = assertTrue(G.handCount[1], testG.handCount[1], 1);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test B finished ***\n");

    printf("\n*** Test C started ***\n");
    assert_value = 0;

    for (i = 0; i < treasure_map + 1; i++)
    {
        result = assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
        assert_value += result;
    }
    printf("Test C ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test C finished ***\n");

    return 0;
}