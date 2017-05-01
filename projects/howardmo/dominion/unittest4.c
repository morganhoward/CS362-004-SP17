/*
Created by Morgan Howard on 4/23/17.
Test the function buyCard()
int buyCard(int supplyPos, struct gameState *state)

Business requirements:
 A. Can only buy as many cards as he has buy actions available (normally 1, but can be more)
 B. Must have enough coins to pay cost of card
 C. Should get correct change from buy
 C. Can't buy from trash (not sure how i would try to do this)
 D. Must be at least one available of the desired card in the supply pile
 E. Player can end turn without using all buys
 F. Rest of the kingdom victory and supply piles are unchanged.
 G. No change in other player's hand
 H. treasure cards (coins) should be played into the play area (not immediately discarded)


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
    printf("\n-------- unittest4 --------\n");
    // init game state
    struct gameState G, testG;
    int assert_value, result;
    int seed = 100;
    int numPlayers = 2;
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

    // Test A --------------------------------------------------------------------------------------
    // check that buyCard checks numBuys
    initializeGame(numPlayers, k, seed, &G);

    // seed hand
    G.hand[0][0] = smithy;
    G.hand[0][1] = village;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    assert_value = 0;

    // check that he only has one buy
    result = assertTrue(testG.numBuys, 1, 1);
    assert_value += result;

    // try to buy two cards
    result = assertTrue(buyCard(copper, &G), 0, 1);
    assert_value += result;

    result = assertTrue(buyCard(copper, &G), -1, 1);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);

    // Test B --------------------------------------------------------------------------------------
    // check that buyCard compares cash in hand with card cost
    initializeGame(numPlayers, k, seed, &G);

    // seed hand
    G.hand[0][0] = smithy;
    G.hand[0][1] = village;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;

    // update coins in hand
    updateCoins(0, &G, 0);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    assert_value = 0;

    // try to buy a card that cost more than what we've got
    result = assertTrue(buyCard(gold, &testG), -1, 1);
    assert_value += result;

    // try to buy a card that we can afford
    result = assertTrue(buyCard(silver, &testG), 0, 1);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    // Test C --------------------------------------------------------------------------------------
    // check that we get correct change
    // BUG: state->coins is properly updated, but the treasure cards in the hand stay in the hand instead of going into played area
    // deals with business req G
    initializeGame(numPlayers, k, seed, &G);

    //printHand(0, &G);
    //printf("coins: %d\n", G.coins);

    // seed hand
    G.hand[0][0] = smithy;
    G.hand[0][1] = village;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;

    updateCoins(0, &G, 0);
    //printHand(0, &G);
    //printf("coins: %d\n", G.coins);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    assert_value = 0;

    //printHand(0, &testG);

    // buy an estate; cost is 2 coins, should have 3 coins to use
    //printf("coins: %d\n", testG.coins);
    buyCard(estate, &testG);

    //printHand(0, &testG);
    //printf("coins: %d\n", testG.coins);

    // we should only have one copper left to spend
    result = assertTrue(testG.coins, 1, 1);
    assert_value += result;

    // we should only have one copper left in our hand
    result = assertTrue(countHandCoins(0, &testG), 1, 1);
    assert_value += result;

    printf("Test C ");
    assertTrue(assert_value, 0, 0);

    // Test D --------------------------------------------------------------------------------------
    // Shouldn't be able to buy from an empty pile
    initializeGame(numPlayers, k, seed, &G);

    // seed hand
    G.hand[0][0] = smithy;
    G.hand[0][1] = village;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    updateCoins(0, &G, 0);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    assert_value = 0;

    //drain estate pile
    testG.supplyCount[estate] = 0;

    // buy an estate; cost is 2 coins, should have 3 coins to use
    buyCard(estate, &testG);

    // shouldn't be able to buy from a drained pile
    result = assertTrue(buyCard(estate, &testG), -1, 1);
    assert_value += result;

    // should be able to buy from a stocked pile
    result = assertTrue(buyCard(estate, &G), 0, 1);
    assert_value += result;

    printf("Test D ");
    assertTrue(assert_value, 0, 0);

    // Test E --------------------------------------------------------------------------------------
    // check that you can end a turn with remaining buys
    assert_value = 0;
    initializeGame(numPlayers, k, seed, &G);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    // check that numBuys is 1
    result = assertTrue(testG.numBuys, 1, 1);
    assert_value += result;

    endTurn(&testG);

    // check that it is now the next player's turn
    result = assertTrue(testG.whoseTurn, 1, 1);
    assert_value += result;

    printf("Test E ");
    assertTrue(assert_value, 0, 0);

    // Test F --------------------------------------------------------------------------------------
    // no change in other player's hand
    assert_value = 0;

    initializeGame(numPlayers, k, seed, &G);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    // buy an estate
    buyCard(estate, &testG);

    result = assertTrue(G.deckCount[1], testG.deckCount[1], 1);
    assert_value += result;

    result = assertTrue(G.handCount[1], testG.handCount[1], 1);
    assert_value += result;

    printf("Test F ");
    assertTrue(assert_value, 0, 0);

    // Test G --------------------------------------------------------------------------------------
    // no change in kingdom and victory card piles
    int i;
    assert_value = 0;

    for (i = 0; i < treasure_map + 1; i++)
    {
        if (i == estate)
        {
            continue;
        }
        result = assertTrue(G.supplyCount[i], testG.supplyCount[i], 1);
        assert_value += result;
    }
    printf("Test G ");
    assertTrue(assert_value, 0, 0);

    return 0;
}