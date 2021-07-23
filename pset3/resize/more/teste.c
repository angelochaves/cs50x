#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{

// ensure proper usage
if (argc != 4)
{
    fprintf(stderr, "Usage: copy infile outfile\n");
    return 1;
}
float f = atof(argv[1]);
if(f<= 0.0 && f>= 100.0)
{
    printf("f is not in range\n");
    return 1;
}

// remember filenames
char *infile = argv[2];
char *outfile = argv[3];

// open input file
FILE *inptr = fopen(infile, "r");
if (inptr == NULL)
{
    fprintf(stderr, "Could not open %s.\n", infile);
    return 2;
}

// open output file
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

BITMAPFILEHEADER nbf = bf;
BITMAPINFOHEADER nbi = bi;
int nf = floor(f);
nbi.biWidth = floor(bi.biWidth*f);
nbi.biHeight = floor(bi.biHeight*f);
int newpadding = (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
nbi.biSizeImage = ((sizeof(RGBTRIPLE))*(nbi.biWidth) + newpadding)* abs(nbi.biHeight);
nbf.bfSize = nbi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

// write outfile's BITMAPFILEHEADER
fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

// write outfile's BITMAPINFOHEADER
fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

// iterate over infile's scanlines
if(f >= 1)
{
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int m = 0; m < nf; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for(int l = 0; l < nf; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
            if( m < (nf-1))
            {
                fseek(inptr, -((bi.biWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
            }
        }
    }
}
else if( f < 1 )
{
    float f2 = 1/f;
    int nf2 = floor(f2);
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 1; j <= bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            if(j%nf2 == 0)
            {
                fseek(outptr, -(sizeof(RGBTRIPLE))*(nf2-1), SEEK_CUR);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < newpadding; k++)
        {
            fputc(0x00, outptr);
        }
        fseek(inptr, ((bi.biWidth * sizeof(RGBTRIPLE)) + padding)*(nf2-1), SEEK_CUR);
    }
}
// close infile
fclose(inptr);

// close outfile
fclose(outptr);

// success
return 0;}