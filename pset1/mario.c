#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int itsMeMario(int height)
{
    int i = 0, j = 0, spaces = 0, k = 0;
    spaces = height - 1;
    if(height >= 0 && height < 24)
    {
        for(i = 0; i < height; i++)
        {
            // Puts spaces before hash tags to create a the desired pyramid
            for(j = 0; j < spaces; j++)
            {
                printf(" ");
            }
            // Prints hashes for each pyramid level
            for(k = 0; k <= i; k++)
            {
                if(k == 0)
                    printf("##");
                else
                    printf("#");
            }
            spaces--;
            printf("\n");
        }
    } else {
        return 1;
    }
    return 0;
}

int main()
{
    int height = 0;

    // Loop for the pyramid function
    do
    {
        //int ch;
        printf("Height: ");
        height = GetInt();
        //while((ch=getchar()) != EOF && ch != '\n'); // Flushes stdin
    } 
    while(itsMeMario(height));

    return 0;
}

