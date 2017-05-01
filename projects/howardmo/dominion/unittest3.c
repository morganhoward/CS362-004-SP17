/*
Created by Morgan Howard on 4/23/17.
Test the function endTurn()
int endTurn(struct gameState *state)

The cleanup phase consists of:
 A. discard player's cards:
    A1. hand
    A2. played action cards
    A3. bought cards
 B. draw a new hand of 5 cards (shuffle discard pile and put it under existing deck, if any)
 C. next player starts their turn

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
    printf("\n-------- unittest3 --------\n");
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

    initializeGame(numPlayers, k, seed, &G);

    // seed hand
    G.hand[0][0] = smithy;
    G.hand[0][1] = village;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = gold;

    // play action cards, change handcount, and buy something
    playCard(1, 0, 0, 0, &G); // play village
    buyCard(province, &G);

    // copy baseline to test state
    memcpy(&testG, &G, sizeof(struct gameState));

    // call the thing we're testing
    endTurn(&testG);

    // Test A --------------------------------------------------------------------------------------
    // check that the player's hand, played action cards, and purchased cards are discarded
    // discard should be old hand + played cards + purchased cards (e.g. 5 + 1 + 1 = 7)
    // BUG: endTurn() doesn't take the cards from the played pile and put them in the discard pile like dominion rules dictate.
    assert_value = 0;

    result = assertTrue(G.handCount[0] + G.playedCardCount + 1, testG.discardCount[0], 1);
    assert_value += result;

    printf("Test A ");
    assertTrue(assert_value, 0, 0);


    // Test B --------------------------------------------------------------------------------------
    // draw a new hand of 5 cards -> check that hand has 5 cards, deck is -5 cards
    // BUG: endTurn() doesn't have former player draw new hand of 5 cards like dominion rules dictate.
    assert_value = 0;

    result = assertTrue(testG.handCount[0], 5, 1);
    assert_value += result;

    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    // Test C --------------------------------------------------------------------------------------
    // next player starts their turn -> check that it is player 1's turn
    assert_value = 0;

    result = assertTrue(whoseTurn(&testG), 1, 1);
    assert_value += result;

    printf("Test C ");
    assertTrue(assert_value, 0, 0);


    return 0;
}