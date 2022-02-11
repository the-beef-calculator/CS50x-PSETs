#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
   int i = 0;
   //variables declared, booleans initialized for input validation
   bool arg1valid = false, arg2valid = false;
   int cipher;
   if (argc == 2)
   {
      arg1valid = true;
   }
   

   // checks to make sure the cipher is only digits, skips if there arent two args
   if (arg1valid == true)
   {
   while (argv[1][i] != '\0')
   {
      if (isdigit(argv[1][i]))
      {
         i++;
      }
      else
      {
         //exits the loop if a non-digit is found, exiting the program
         arg2valid = false;
         break;
      }
         //sets value to true once the end of the array is reached without any errors
      if (argv[1][i] =='\0')
      {
         arg2valid = true;
      }
   }
   } //unlocks next part of program if both the inputs are valid
   if (arg1valid == true && arg2valid == true)
   {
       char alphabet[] = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122};
       // converts a char to int
       cipher = atoi(argv[1]);
       // adjusts case for capital letters
       bool casesense = false;
       string input = get_string("plaintext: ");
       int length = strlen(input);
       printf("ciphertext: ");
       
       
       for (int j = 0; j < length; j++)
       {
          //skips iteration if punctuation or blankspace is found
          if (isspace(input[j]))
          {
             printf(" ");
             continue;
          }
          if (ispunct(input[j]))
          {
             printf("%c", input[j]);
             continue;
          }
          for (int k = 0; k < 26; k++)
          {
             
             if (isupper(input[j]))
                {
                   input[j] = tolower(input[j]);
                   casesense = true;
                }
             if (input[j] == alphabet[k])
             {
                // calculates the cipher obtain index location, stored in code
                int code = (k + cipher) % 26;
                if (casesense == true)
                {
                   alphabet[code] = toupper(alphabet[code]);
                   casesense = false;
                   
                }

                printf("%c", alphabet[code]);
                alphabet[code] = tolower(alphabet[code]);
                k = 27;
             }
             
          } 
          
          
       } printf("\n");
      
   }  
   else
   {
      printf("Usage: ./caesar key\n");
      return 1;
   }

}