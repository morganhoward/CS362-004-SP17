/*
Created by Morgan Howard on 4/23/17.
Test Adventurer card
 - Reveal cards from your deck until you reveal 2 treasure cards.
 - Put those treasure cards in your hand.
 - Discard the other revealed cards.

 Business requirements:
 A. hand has two more treasure cards than before playing adventurer
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

int count_treasure_cards(struct gameState *state)
{
    int i = 0;
    int treasure_count = 0;
    int curCard = 0;

    for (i = 0; i < MAX_HAND; i++)
    {
        curCard = state->hand[0][i];
        if (curCard == copper || curCard == silver || curCard == gold)
        {
            treasure_count++;
        }
    }

    return treasure_count;
}

int main()
{
    printf("\n-------- cardtest2 --------\n");
    // init game state
    struct gameState G, testG;
    int assert_value, result;
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
    G.hand[0][0] = adventurer;
    memcpy(&testG, &G, sizeof(struct gameState));

    // play card
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // Test A --------------------------------------------------------------------------------------
    // hand has two more treasure cards than before playing adventurer
    int treasure_test = 0;
    int treasure_baseline = 0;
    assert_value = 0;

    treasure_test = count_treasure_cards(&testG);
    treasure_baseline = count_treasure_cards(&G);
    result = assertTrue(treasure_test - 2, treasure_baseline, 1);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);


    // Test B --------------------------------------------------------------------------------------
    // after playing, the test hand should have 1 more card (+2 treasure, - 1 adventurer) in hand than the baseline
    assert_value = 0;

    // BUG: this catches the bug where the adventurer card isn't discarded immediately after being played
    result = assertTrue(testG.handCount[0] - 1, G.handCount[0], 1);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    //printHand(0, &G);
    //printHand(0, &testG);

    // Test C --------------------------------------------------------------------------------------
    //change in deck (x) + 2 should be equal to change in discard (y) ... y = x - 2
    assert_value = 0;
    int delta_discard, delta_deck;


    delta_discard = testG.discardCount[0] - G.discardCount[0];
    delta_deck = G.deckCount[0] - testG.deckCount[0];
    result = assertTrue(delta_deck - 2, delta_discard, 1);
    assert_value += result;

    //printHand(0, &G);
    //printHand(0, &testG);

    printf("Test C ");
    assertTrue(assert_value, 0, 0);

    // Test D --------------------------------------------------------------------------------------
    // no change in other player's hand
    assert_value = 0;
    result = assertTrue(G.deckCount[1], testG.deckCount[1], 1);
    assert_value += result;

    result = assertTrue(G.handCount[1], testG.handCount[1], 1);
    assert_value += result;

    printf("Test D ");
    assertTrue(assert_value, 0, 0);

    // Test E --------------------------------------------------------------------------------------
    // no change in kingdom and victory card piles
    int i;
    assert_value = 0;

    for (i = 0; i < treasure_map + 1; i++)
    {
        result = assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
        assert_value += result;
    }
    printf("Test E ");
    assertTrue(assert_value, 0, 0);

    return 0;
}