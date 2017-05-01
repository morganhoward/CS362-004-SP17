/*
Name: Morgan Howard
ONID: howardmo
Class: CS362
Assignment: Random Testing Quiz 2
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// produces a random ascii char from 40-127
// highest ascii value of chars testme() is checking for is space (127)
char inputChar()
{
    char rand_char = (char) (rand() % 127 + 1);
    return rand_char;
}


// produces a random string of 5 alphabet characters
char *inputString()
{
    // vars
    int len = 6;
    int i = 0;
    char rand_string [len];

    // null out string
    memset(rand_string, '\0', len - 1);

    // generate string
    for (i = 0; i < len; i++)
    {
        rand_string[i] = (char) (rand() % 26) + 97;
    }
    rand_string[len] = '\0';

    // assign string to pointer and return
    char *str = rand_string;
    //char *tst = "reset";
    return str;
}


/*
 *
 */
void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
