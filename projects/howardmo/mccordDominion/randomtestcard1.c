/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: 4

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
#include <math.h>

#define DEBUG 1

/* bash-style return vals, 0 = true, 1 = false
 noise values:
 0 - print both
 1 - print only fail
 2 - print nothing
 */
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

int main() {
    printf("\n-------- randomcardtest1 --------\n");

    // vars
    struct gameState before, after;
    int assert_value, i, result, n, p, deckCount, discardCount, handCount, handPos, bonus, choice1, choice2, choice3;
    int number_of_tests = 10000;
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
        if (DEBUG)
            printf("\n*** n = %d ***\n", n);

        // init game state
        result = initializeGame(MAX_PLAYERS, k, n + 1, &before);
        choice1 = 0;
        choice2 = 0;
        choice3 = 0;
        bonus = 0;

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

        // play card in after
        //card_smithy(&after, p, handPos);
        cardEffect(smithy, choice1, choice2, choice3, &after, handPos, &bonus);

        // Test A --------------------------------------------------------------------------------------
        // player should draw 3 cards (hand: +3 - 1; deck: -3; played: +1)
        assert_value = 0;

        // BUG: this caught the bug i introduced for assignment 2; smithy drawing 4 cards instead of 3
        result = assertTrue(before.deckCount[p] - 3, after.deckCount[p], 0);
        assert_value += result;

        // BUG: this also caught the same bug caught above; smithy is drawing 4 cards instead of 3
        // hand should have +3 cards from the draw and -1 from discarding smithy
        result = assertTrue(before.handCount[p] + 3 - 1, after.handCount[p], 0);
        assert_value += result;

        // test hand playedcardcount should be one more than baseline (played adventurer)
        result = assertTrue(before.playedCardCount + 1, after.playedCardCount, 0);
        assert_value += result;

        if (DEBUG)
            printf("Test A ");
        assertTrue(assert_value, 0, 0);

        // Test B --------------------------------------------------------------------------------------
        // no state change for other players
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

        if (DEBUG)
            printf("Test B ");
        assertTrue(assert_value, 0, 0);

        // Test C --------------------------------------------------------------------------------------
        // no state change to victory and kingdom card piles
        assert_value = 0;

        for (i = 0; i < treasure_map + 1; i++) {
            result = assertTrue(before.supplyCount[i], after.supplyCount[i], 1);
            assert_value += result;
        }

        if (DEBUG)
            printf("Test C ");
        assertTrue(assert_value, 0, 0);
    }
    return 0;
}