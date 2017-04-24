/*
Created by Morgan Howard on 4/23/17.
Test great hall
 +1 card
 +1 action
 +1 victory point

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

    return 0;
}