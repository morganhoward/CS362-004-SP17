/*
Created by Morgan Howard on 4/23/17.
Test the function getCost()
getCost returns the coin cost of a card.  I manually checked the values in the dominion wiki and added them to
 card_costs[], which can now automatically check the getCost().

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
    printf("\n-------- unittest2 --------\n");
    int card_costs[26] = {0, 2, 5, 8, 0,
                          3, 6, 6, 5, 4,
                          4, 5, 4, 4, 3,
                          4, 3, 5, 3, 5,
                          3, 4, 2, 5, 4, 4};
    char card_name[15];
    int cost = 0;
    int i = 0;
    int assert_value = 0;

    // Test A --------------------------------------------------------------------------------------
    for (i = 0; i < 26; i++)
    {
        cardNumToName(i, card_name);
        //printf ("%s: ", card_name);
        cost = getCost(i);
        assert_value = assertTrue(cost, card_costs[i], 1);
        assert_value += assert_value;
    }

    printf("Test A ");
    assertTrue(assert_value, 0, 0);

    return 0;
}