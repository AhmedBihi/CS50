/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4){
        printf("Usage: n infile outfile\n");
        return 1;
    }
    
    char* infile = argv[2];
    char* outfile = argv[3];
    char *s = argv[1];
    int n = 0;
    
    // Checks if argument 1 is a digit
    while(*s){
        if(!isdigit(*s++)) {
            printf("Usage: n infile outfile\n");
                return 1;
        } else {
            break;
        }
    }
    
    // n to integer, checks if n is 1-100
    n = atoi(argv[1]);
    if(n > 100 || n < 1) {
        printf("Usage: n infile outfile\n %d, n: 1-100.\n", n);
        return 1;
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
     
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0) 
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }
    
    // update outfile width and height
    int oldWidth   = bi.biWidth;
    int oldHeight  = bi.biHeight;
    bi.biWidth     = bi.biWidth * n;
    bi.biHeight    = bi.biHeight * n;
    
    // determine padding for in/output file
    int padding     =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpadding  =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update outfile size
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + abs(outpadding)) * abs(bi.biHeight);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (bi.biSizeImage);
    
    // write outfile's BITMAPFILEHEADER & BITMAPINFOHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // write scanline n times
        for(int c = 0; c < n; c++)
        {   
            // iterate over pixels in scanline
            for (int j = 0; j < oldWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile n times
                for(int k = 0; k < n; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // then add it back (to demonstrate how)
            for (int pad = 0; pad < outpadding; pad++)
                fputc(0x00, outptr);
                
            if (c < n-1)
                fseek(inptr, (-oldWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
         }
         // skip over padding, if any
         fseek(inptr, padding, SEEK_CUR); 
    }
    
    // close infile & outfile
    fclose(inptr);
    fclose(outptr);

    // that's all folks
    return 0;
}
