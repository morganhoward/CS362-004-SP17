/*
Created by Morgan Howard on 4/23/17.
Test village
+1 card
+2 actions

 Business requirements:
 A. player draws one card (has same number of cards after playing; e.g. +1 -1)
 B. player has two more actions after playing card (e.g. 3 available actions)
 C. no state change for other players
 D. no state change to victory and kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

/* bash-style return vals, 0 = true, 1 = false
 noise values:
 0 - print both
 1 - print only fail
*/
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
    printf("\n-------- cardtest3 --------\n");
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
    G.hand[0][0] = village;
    memcpy(&testG, &G, sizeof(struct gameState));

    //printHand(0, &G);
    //printHand(0, &testG);

    // play card
    cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

    //printHand(0, &G);
    //printHand(0, &testG);

    // Test A --------------------------------------------------------------------------------------
    // hand count is the same (+1 -1) but discard pile is +1
    // Found Bug: discardCard() doesn't add to discard pile (which is correct according to rules but fxn name is misleading);
    // however, endTurn() should move played cards to the discard pile but it doesn't.
    assert_value = 0;

    result = assertTrue(G.handCount[0], testG.handCount[0], 1);
    assert_value += result;

    /*
    printDiscard(0, &testG);
    printPlayed(0, &testG);
    endTurn(&testG);
    printDiscard(0, &testG);
    printPlayed(0, &testG);
    printf("%d %d\n", G.discardCount[0], testG.discardCount[0]);
    result = assertTrue(G.discardCount[0] +1, testG.discardCount[0], 1);
     */
    result = assertTrue(G.playedCardCount + 1, testG.playedCardCount, 1);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);

    // Test B --------------------------------------------------------------------------------------
    // player has two more actions after playing card (e.g. 3 available actions)
    // Found Bug: this caught the bug I added in assignment-2 where village adds 3 actions instead of 2
    assert_value = 0;

    result = assertTrue(G.numActions + 2, testG.numActions, 1);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    // Test C --------------------------------------------------------------------------------------
    // no change in other player's hand
    assert_value = 0;
    result = assertTrue(G.deckCount[1], testG.deckCount[1], 1);
    assert_value += result;

    result = assertTrue(G.handCount[1], testG.handCount[1], 1);
    assert_value += result;

    printf("Test C ");
    assertTrue(assert_value, 0, 0);

    // Test D --------------------------------------------------------------------------------------
    // no change in kingdom and victory card piles
    assert_value = 0;

    for (i = 0; i < treasure_map + 1; i++)
    {
        result = assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
        assert_value += result;
    }
    printf("Test D ");
    assertTrue(assert_value, 0, 0);


    return 0;
}