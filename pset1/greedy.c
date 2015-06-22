#include <stdio.h>
#include <cs50.h>
#include <math.h>

int coins(float input)
{
    input = input*100;
    int cents = (int) round(input);

    if(cents < 0)
        return 1;

    int coins = 0;
    while(cents >= 1)
    {
        if(cents >= 25)
        {
            cents = cents - 25;
        }
        else if(cents < 25 && cents >= 10)
        {
            cents = cents - 10;
        }
        else if(cents < 10 && cents >= 5)
        {
            cents = cents - 5;
        }
        else
        {
            cents = cents - 1;
        }
        coins++;
    }
    printf("%d\n", coins);
    return 0;
}

int main()
{
    float input;
    do
    {
        printf("O hai! How much change is owed?\n");
        input = GetFloat();
    }
    while(coins(input));

    return 0;
}

