/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: 4

Random test for the Adventurer card.

Test Adventurer card
 - Reveal cards from your deck until you reveal 2 treasure cards.
 - Put those treasure cards in your hand.
 - Discard the other revealed cards.

 Notes:
 - If you run out of cards in the deck, shuffle your discard pile

 Business requirements:
 A. hand has no more than two more treasure cards than before playing adventurer
 B. number of cards in hand is n + 2 - 1 (+2 treasure, -1 adventurer discard)
 C. change in deck (x) + 2 should be equal to change in discard (y) ... y = x - 2
 D. no change in other player's hand
 E. no change in kingdom and victory card piles

 > make clean; make cardtest2; cardtest2
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"
#include <math.h>

#define DEBUG 0

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

int count_treasure_cards(int p, struct gameState *state) {
    int i = 0;
    int treasure_count = 0;
    int curCard = 0;
    int size = state->handCount[p];

    for (i = 0; i < size; i++) {
        curCard = state->hand[p][i];
        if (curCard == copper || curCard == silver || curCard == gold) {
            treasure_count++;
        }
    }

    return treasure_count;
}

// TODO?: fill cards between size and MAX_??? with 0's or another int?
void fillCardPiles(int *pile, int size) {
    // vars
    int i = 0;

    // fill pile with valid kingdom cards, curse=0 to treasure_map
    for (i = 0; i < size; i++) {
        pile[i] = floor(Random() * (treasure_map + 1));
    }
}


int checkAdventurerCard(int p, struct gameState *before, struct gameState *after, int deckCount, int discardCount,
                        int handCount) {
    int assert_value, result, i;

    // Test A --------------------------------------------------------------------------------------
    // hand has two more treasure cards than before playing adventurer
    int treasure_test = 0;
    int treasure_baseline = 0;
    assert_value = 0;

    treasure_baseline = count_treasure_cards(p, before);
    treasure_test = count_treasure_cards(p, after);

    if (DEBUG) {
        printf("before card play:\n");
        printHand(p, before);
    }

    if (DEBUG) {
        printf("after card play:\n");
        printHand(p, after);
    }


    result = assertTrue(treasure_test - 2, treasure_baseline, 2);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);

    // Test B --------------------------------------------------------------------------------------
    // after playing, the test hand should have 1 more card (+2 treasure, - 1 adventurer) in hand than the baseline
    assert_value = 0;

    // BUG: this catches the bug where the adventurer card isn't discarded immediately after being played
    result = assertTrue(before->handCount[p], after->handCount[p] - 1, 2);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    // Test C --------------------------------------------------------------------------------------
    //change in deck (x) + 2 should be equal to change in discard (y) ... y = x - 2
    assert_value = 0;
    int delta_discard, delta_deck;

    delta_discard = after->discardCount[p] - before->discardCount[p];
    delta_deck = before->deckCount[p] - after->deckCount[p];
    result = assertTrue(delta_deck - 2, delta_discard, 2);
    assert_value += result;

    printf("Test C ");
    assertTrue(assert_value, 0, 0);

    // Test D --------------------------------------------------------------------------------------
    // no change in other players' hand
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (i == p) {
            continue;
        }
        assert_value = 0;
        result = assertTrue(before->deckCount[i], after->deckCount[i], 2);
        assert_value += result;

        result = assertTrue(before->handCount[i], after->handCount[i], 2);
        assert_value += result;
    }

    printf("Test D ");
    assertTrue(assert_value, 0, 0);

    // Test E --------------------------------------------------------------------------------------
    // no change in kingdom and victory card piles
    assert_value = 0;

    for (i = 0; i < treasure_map + 1; i++) {
        result = assertTrue(before->supplyCount[i], after->supplyCount[i], 2);
        assert_value += result;
    }
    printf("Test E ");
    assertTrue(assert_value, 0, 0);

    return 0;
}


int main() {
    // vars
    struct gameState before, after;
    int number_of_tests = 10000;
    int i = 0;
    int p = 0;
    int n = 0;
    int deckCount = 0;
    int discardCount = 0;
    int handCount = 0;
    int handPos = 0;
    int result = 0;
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
        printf("\n*** n = %d ***\n", n);

        // init game state
        result = initializeGame(MAX_PLAYERS, k, n + 1, &before);
        if (DEBUG)
            printf("numPlayers is: %d \n\n", before.numPlayers);

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

        if (DEBUG)
            printf("deckCount=%d, discardCount=%d, handCount=%d, handPos=%d \n\n", deckCount, discardCount, handCount,
                   handPos);

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
        if (DEBUG)
            printHand(p, &before);

        // set turn for player p
        before.whoseTurn = p;

        // give player p the adventurer card at handPos
        before.hand[p][handPos] = adventurer;

        // seed two treasure cards at bottom of deck
        before.deck[p][0] = copper;
        before.deck[p][1] = copper;

        if (DEBUG)
            printDeck(p, &before);

        // copy state1 to state2
        memcpy(&after, &before, sizeof(struct gameState));

        // play adventurer card in state2
        card_adventurer(&after, p);

        // perform expected actions for adventurer card in state2

        //compare state1 and state2
        checkAdventurerCard(p, &before, &after, deckCount, discardCount, handCount);

    }


    return 0;
}

