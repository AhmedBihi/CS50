/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char *buffer;
    char jpeg_name[8];
    char jpeg_sign0[4] = {0xff, 0xd8, 0xff, 0xe0};
    char jpeg_sign1[4] = {0xff, 0xd8, 0xff, 0xe1};
    int jpeg_num = 0;
    FILE* image = NULL;
    
    // open the card file
    FILE* cr = fopen("card.raw", "r");
    if(cr == NULL){ 
        fclose(cr); 
        printf("Can't open card.raw!\n"); 
        return 1; 
    }
    
    // create a buffer for 512 bytes using calloc (puts 0's in each byte).
    buffer = (char*) calloc (512, sizeof(char));
    if (buffer == NULL) { printf("Memory error\n"); return 2; }
    
    while(fread(buffer, 512, 1, cr)) 
    {
        if(memcmp(buffer, jpeg_sign0, 4) == 0 || memcmp(buffer, jpeg_sign1, 4) == 0)
        {
            // closes the latest ".jpg" file
            if(image) { fclose(image); }
            
            // creates a filename
            sprintf(jpeg_name, "%03d.jpg", jpeg_num);
            
            // open a new ".jpg" file for writing
            image = fopen(jpeg_name, "w"); 
            if(!image) { fclose(image); printf("Cant open %03d.jpg\n", jpeg_num); return 3;}
            
            // write 512 bytes in the new .jpg file
            fwrite(buffer, 512, 1, image);
            
            // increment filename number
            jpeg_num++; 
        } 
        else if(image) 
        {
            // if file is still open, keep writing blocks
            fwrite(buffer, 512, 1, image);
        }
    }  
    
    free(buffer);
    fclose(cr);
    fclose(image);
    
    return 0;
}
