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
    return 0;
}