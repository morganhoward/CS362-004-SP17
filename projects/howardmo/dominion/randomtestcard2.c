/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: 4

Random test for village card
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
#include <math.h>

#define DEBUG1 1
#define DEBUG2 0

int assertTrue(int value1, int value2, int noise) {
    int assert_result = -1;
    if (value1 == value2) {
        if (noise == 0) {
            printf("PASS\n");
        }
        assert_result = 0;
    } else {
        if (noise < 2) {
            printf("FAIL %d %d\n", value1, value2);
        }
        assert_result = 1;
    }
    return assert_result;
}

int main()
{
    printf("\n-------- randomcardtest2 --------\n");
    // init game state
    struct gameState before, after;
    int assert_value, i, result, n, p, deckCount, discardCount, handCount, handPos;
    int number_of_tests = 100;
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

    for (n = 0; n < number_of_tests; n++) {
        if (DEBUG1)
            printf("\n*** n = %d ***\n", n);

        // init game state
        result = initializeGame(MAX_PLAYERS, k, n + 1, &before);

        // randomize game state
        // narrowly randomize important properties
        p = floor(Random() * MAX_PLAYERS);    // randomly choose player
        deckCount = floor(Random() * (MAX_DECK + 1));    // randomly set number of cards in deck, 0 - MAX_DECK-1
        before.deckCount[p] = deckCount;

        discardCount = floor(Random() * (MAX_DECK + 1));    // randomly set number of cards in discard, 0 - MAX_DECK
        before.discardCount[p] = discardCount;

        handCount = floor(Random() * MAX_HAND) + 1;  // randomly set number of cards in hand, 1 - MAX_HAND
        before.handCount[p] = handCount;

        handPos = floor(Random() * (handCount - 1));     // randomly set hand position for adventurer card

        // fill the piles using their random sizes
        for (i = 0; i < deckCount; i++) {
            before.deck[p][i] = floor(Random() * (treasure_map + 1));
        }
        for (i = 0; i < discardCount; i++) {
            before.discard[p][i] = floor(Random() * (treasure_map + 1));
        }
        for (i = 0; i < handCount; i++) {
            before.hand[p][i] = floor(Random() * (treasure_map + 1));
        }

        // set turn for player p
        before.whoseTurn = p;

        // give player p the adventurer card at handPos
        before.hand[p][handPos] = smithy;

        // copy before to after
        memcpy(&after, &before, sizeof(struct gameState));

        if (DEBUG2) {
            printHand(p, &before);
            printHand(p, &after);
        }

        // play card in after
        card_village(&after, p, handPos);

        if (DEBUG2) {
            printHand(p, &before);
            printHand(p, &after);
        }

        // Test A --------------------------------------------------------------------------------------
        // hand count is the same (+1 -1) but discard pile is +1
        // Found Bug: discardCard() doesn't add to discard pile (which is correct according to rules but fxn name is misleading);
        // however, endTurn() should move played cards to the discard pile but it doesn't.
        assert_value = 0;

        result = assertTrue(before.handCount[0], after.handCount[0], 1);
        assert_value += result;

        result = assertTrue(before.playedCardCount + 1, after.playedCardCount, 1);
        assert_value += result;

        //printf("Test A ");
        assertTrue(assert_value, 0, 1);

        // Test B --------------------------------------------------------------------------------------
        // player has two more actions after playing card (e.g. 3 available actions)
        // Found Bug: this caught the bug I added in assignment-2 where village adds 3 actions instead of 2
        assert_value = 0;

        result = assertTrue(before.numActions + 2, after.numActions, 1);
        assert_value += result;

        //printf("Test B ");
        assertTrue(assert_value, 0, 1);

        // Test C --------------------------------------------------------------------------------------
        // no change in other player's hand
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (i == p) {
                continue;
            }
            assert_value = 0;
            result = assertTrue(before.deckCount[i], after.deckCount[i], 1);
            assert_value += result;

            result = assertTrue(before.handCount[i], after.handCount[i], 1);
            assert_value += result;
        }

        //printf("Test C ");
        assertTrue(assert_value, 0, 1);

        // Test D --------------------------------------------------------------------------------------
        // no change in kingdom and victory card piles
        assert_value = 0;

        for (i = 0; i < treasure_map + 1; i++) {
            result = assertTrue(before.supplyCount[i], after.supplyCount[i], 1);
            assert_value += result;
        }
        //printf("Test D ");
        assertTrue(assert_value, 0, 1);
    }

    return 0;
}