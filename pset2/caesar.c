#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
                if(n == 122 || n == 90)
                {
                    if(n == toupper(n))
                        n = 65;
                    else
                        n = 97;
                }
                else 
                {  
                    n++;
                }
            }
        }
        printf("%c", n);
    }
    printf("\n");
}

int main(int argc, string argv[])
{
    char *message;
    
    if(argc < 2 || argc > 2){
        printf("Only 1 argument please!\n");
        return 1;
    }
        
    message = GetString();
    int k = atoi(argv[1]);
    
    ceasar(message, k);

    return 0;
}
