#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{


    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }


}



int compute_score(string word)
{
    int t = 0;
    char alphabet[] = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
    //captures length of string and stores into variable
    int o = strlen(word);



    //loop that goes through each character in given string
    for (int i = 0; i < o;  i++)
    {
        char p = word[i];
        //checks if stored character is an uppercase
        if (isupper(p) )
        {
           p = tolower(p);
           word[i] = p;
        }

        //for loop that traverses entire alphabet array searching for a match

        for(int j = 0; j < 26 ; j++)
        {
           if (word[i] == alphabet[j])
           {
               t += POINTS[j];
               //skips to the end of the loop after finding a match
               j = 27;
           }

        }
    }

    return t;
}
