/*
Created by Morgan Howard on 4/23/17.
Test the function endTurn()
int endTurn(struct gameState *state)

The cleanup phase consists of:
 A. discard player's hand
 B. discard all action cards
 C. discard all bought cards
 D. draw a new hand of 5 cards (shuffle discard pile and put it under existing deck, if any)
 E. next player starts their turn

 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "interface.h"

// bash-style return vals, 0 = true, 1 = false
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
        if (noise == 0)
        {
            printf("FAIL %d %d\n", value1, value2);
        }
        assert_result = 1;
    }
    return assert_result;
}

int main()
{
    // init game state
    struct gameState G, testG;
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

    printf("*** Test A started ***\n");
    printf("Test A ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test A finished ***\n");

    printf("*** Test B started ***\n");
    printf("Test B ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test B finished ***\n");

    printf("*** Test C started ***\n");
    printf("Test C ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test C finished ***\n");

    printf("*** Test D started ***\n");
    printf("Test D ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test D finished ***\n");

    printf("*** Test E started ***\n");
    printf("Test E ");
    assertTrue(assert_value, 0, 0);
    printf("*** Test E finished ***\n");

    return 0;
}