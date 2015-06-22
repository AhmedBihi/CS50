#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void vigenere(char *message, char *keyword)
{
    int keylen = strlen(keyword),  len = strlen(message);
    int i, count = 0, j= 0;
    char keyarray[100];
    char chiper[100];
    for(i = 0; i<len; i++)
    {
        if(isalpha(message[i]))
        {
            keyarray[i] = keyword[count];
            count++;
        }
        else
        {
            keyarray[i] = message[i];
        }

        if(count >= keylen)
            count = 0;
    }

    for(i = 0; i<len; i++)
    {
        if(isalpha(keyarray[i]))
        {
            if(isupper(message[i]))
            {
                chiper[i] = (message[i] - 65 + keyarray[j] - 65) % 26;
                chiper[i] = chiper[i] + 65;
            }
            else
            {
                chiper[i] = (message[i] - 97 + tolower(keyarray[j]) - 97) % 26;
                chiper[i] = chiper[i] + 97;
            }
            j++;
        }
        else
        {
            chiper[i] = keyarray[i];
            j++;
        }
    }
    
    printf("%s\n", chiper);
}

int main(int argc, string argv[])
{
    char *message;
    int n, i;
    
    if(argc < 2 || argc > 2)
    {
        printf("Only 1 argument please!\n");
        return 1;
    }
    
    for(i = 0, n = strlen(argv[1]); i<n; i++)
    {
        if(!isalpha(argv[1][i]))
        {
            printf("Only letters as keyword");
            return 1;
        }
    }
        
    message = GetString();
    
    vigenere(message, argv[1]);

    return 0;
}

