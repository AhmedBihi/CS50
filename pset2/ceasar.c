#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LOWMAX 122
#define HIGHMAX 90
#define ASCIIALPHA 65
#define ASCIILOWER 97

void ceasar(char *message, int k)
{
    int n, i, j, len = strlen(message);

    for(i = 0; i<len; i++)
    {
        n = message[i];
        if(isalpha(n))
        {
            for(j = 0; j<k; ++j)
            {
                if(n == LOWMAX || n == HIGHMAX)
                {
                    if(n == toupper(n))
                        n = ASCIIALPHA;
                    else
                        n = ASCIILOWER;
                }
                n++;
            }
        }
        printf("%c", n);
    }
    printf("\n");
}

int main(int argc, string argv[])
{
    char *message;
    
    if(argc < 2)
        return 1;
    
    message = GetString();
    int k = atoi(argv[1]);
    
    ceasar(message, k);

    return 0;
}
