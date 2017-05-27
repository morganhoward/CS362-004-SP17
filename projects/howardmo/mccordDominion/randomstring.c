/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: Random Testing Quiz 2

Objective:
 For this quiz, I developed a random tester.  More specifically, the instructions were to write up implementations
 of inputChar() and inputString() that would satisfy the requirements of testme() and get to the "error" print statement.
 Also, we weren't supposed to modify anything outside of those two functions.

Comments:
 For inputChar(), the if blocks in testme() covered ASCII values from 40 (left parenthesis) - 127 (space).  As the random
 value of inputChar() matched each subsequent if block, an int value "state" incremented (up to 9).  It was pretty quick
 to get to state=9, and once there, it tried to match inputString() to "reset" (null-terminated string).  If you matched
 that last if block, you get a print statement ("error") and an exit code of 200.

 I coded inputChar() to randomly cycle through the values 40-127, and hardcoded inputString() as "reset"; time-wise, it
 was relatively quick but it still took 1639 iterations to get to the end.  Then, I removed the hard-coded string from
 inputString() and coded it to randomly generate an five character alpha string because testme() only checks inputString()
 for alphabet characters.  I ran it for a little while and got to the 123,189,304th iteration before I interrupted it
 because my computer was getting sluggish.

*/

