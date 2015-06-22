#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void initials(char *name)
{
    char init[5];
    int i, count = 1;
    for(i = 0; i<strlen(name); i++){
        if(i == 0){
            init[i] = toupper(name[i]);
        }
        if(name[i] == ' '){
            init[count] = toupper(name[i+1]);
            count++;
        }
    }
    printf("%s\n", init);
}

int main()
{
    char *name;
    
    name = GetString();
    
    initials(name);
    
    return 0;
}

