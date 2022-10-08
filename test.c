#include <stdio.h>
#include <string.h>
int main (void)
{
    char block[] = "#";
    for (int i = 0; i < 8; i++)
    {
        strcat(block,"#");
        printf("%s\n",block);
    }

}
