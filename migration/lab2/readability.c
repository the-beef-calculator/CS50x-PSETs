#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int verify_count();

int main(void)
{
    string a = get_string("Text: ");
    
    verify_count(a);
    
    
}

int verify_count(string word)
{
    //stores size of string as an integer
    
    int o = strlen(word);
    const int SIZE = o;
    
    //declaring variables
    
    int wordCount = 1;
    int sentCount = 0;
    
    //verifies each character of string
    
    for (int i = 0; i < SIZE ; i++)
    {
        if (isalpha(word[i]) == false)
        {
            o--;
        }
        if (isspace(word[i]))
        {
            wordCount++;
        }
        if (word[i] == '?' || word[i] == '!' || word[i] == '.')
        {
            sentCount++;
        }
    
    }
    // formula for the index
    float L = ((float)o / wordCount * 100);
    float S = ((float)sentCount / wordCount * 100);
    
    float index = (0.0588 * L - 0.296 * S - 15.8);
  
    //making sure data is accurate
    printf("%i letter(s).\n", o);
    printf("%i word(s).\n", wordCount);
    printf("%i sentence(s).\n", sentCount);
  
    //final conditions
    if ((int) round(index) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if ((int) round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else 
    {
        printf("Grade %i\n", (int) round(index)); 
    }
    return 0;
}