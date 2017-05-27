/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: 3

Test the function isGameOver()

Game ending conditions for dominion are:
 A. The province pile is empty
 B. Any three supply piles are empty (2-4 players), or four piles (5+ players)
 C. The colony pile is empty (N/A - not using colony cards)

 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


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
    printf("\n-------- unittest1 --------\n");
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

    // make copy of the game state
    memcpy(&testG, &G, sizeof(struct gameState));

    // Test A --------------------------------------------------------------------------------------
    // Check if isGameOver returns 1 if there are 0 provinces

    int assert_value = 0;
    int result = 13;
    int i = 0;
    int numVictoryCardsEach = 8;
    for (i = 0; i < numVictoryCardsEach + 1; i++)
    {
        //printf("%d: ", i);
        result = isGameOver(&G);
        if (i == numVictoryCardsEach)
        {
            assert_value = assertTrue(result, 1, 1);
            assert_value += assert_value;
        }
        else
        {
            assert_value = assertTrue(result, 0, 1);
            assert_value += assert_value;
        }
        G.supplyCount[province]--;
    }
    printf("Test A ");
    assertTrue(assert_value, 0, 0);

    // Test B --------------------------------------------------------------------------------------
    // Check if isGameOver returns 1 when three supply piles are zeroed out

    assert_value = 0;
    int assert_value1 = 0;
    int assert_value2 = 0;
    result = 13;
    struct gameState testB;
    int i1, i2, i3;
    for (i1 = 0; i1 < 8; i1++)
    {
        for (i2 = i1 + 1; i2 < 9; i2++)
        {
            for (i3 = i2 + 1; i3 < 10; i3++)
            {
                if (i2 == i3)
                {
                    continue;
                }

                //printf("iter [%d, %d, %d]: \n", i1, i2, i3);
                initializeGame(numPlayers, k, seed, &testB);

                //printf("\tpre check: ");
                result = isGameOver(&testB);
                assert_value1 = assertTrue(result, 0, 1);
                assert_value += assert_value1;

                testB.supplyCount[i1] = 0;
                testB.supplyCount[i2] = 0;
                testB.supplyCount[i3] = 0;

                //printf("\tpost check: ");
                result = isGameOver(&testB);
                assert_value2 = assertTrue(result, 1, 1);
                assert_value += assert_value2;
            }
        }
    }
    printf("Test B ");
    assertTrue(assert_value, 0, 0);

    return 0;
}