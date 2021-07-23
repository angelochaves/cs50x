#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

    //Tests for argument number and argument 1 as null
    if (argc != 4 || atoi(argv[1]) <= 0 || atoi(argv[1]) > 100 || argv[2] == '\0' || argv[3] == '\0')
    {
        printf("\nUsage: ./resize n infile outfile\n\n");
        return 1;
    }

    //Remembers arguments
    int n = atoi(argv[1]);
    int col = 0;
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //Opens output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
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
        return 4;
    }

    //Calculates padding of the infile
    int paddingin = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Calculates new width
    bi.biWidth *= n;

    //Calculates new padding, i.e, of the outfile
    int paddingout = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Calculates new height
    bi.biHeight *= n;

    //Updates biSizeImage and bfSize
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + paddingout) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = (abs(bi.biHeight) / n); i < biHeight; i++)
    {
        //Resets fseek
        col = 0;

        //Writes scanline to outfile 'n' times, vertically
        for (int j = 0; j < n; j++)
        {
            if (col != 0)
            {
                fseek(inptr, -((sizeof(RGBTRIPLE) * (bi.biWidth / n)) + paddingin), SEEK_CUR);
            }

            // iterate over pixels in scanline
            for (int k = 0; k < (bi.biWidth / n); k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //Writes scanline to outfile 'n' times, horizontally
                for (int l = 0; l < n; l++)
                {
                   fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, paddingin, SEEK_CUR);

            //then add it back (to demonstrate how)
            for (int m = 0; m < paddingout; m++)
            {
                fputc(0x00, outptr);
            }

            //Triggers fseek to return the inptr scanline
            col = 1;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}