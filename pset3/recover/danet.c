#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{

    //Tests for argument number and argument 1 as null
    if (argc != 2 || argv[1] == '\0')
    {
        printf("\nUsage: ./recover image\n\n");
        return 1;
    }

    //Opens input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    int namecount = 0;
    int newf = 1;
    unsigned char *buffer = malloc(sizeof(char) * 512);
    FILE *outfile = NULL;
    char outname[8];

    //Iterates to create next file name
    while (fread(buffer, 1, 512, inptr) > 0)
    {
        //New outfile?
        if (newf == 1)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                sprintf(outname, "%03i.jpg", namecount);
                outfile = fopen(outname, "w");
                fwrite(buffer, 1, 512, outfile);
                newf = 0;
            }
        }
        else if (newf == 0)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                fclose(outfile);
                namecount++;
                sprintf(outname, "%03i.jpg", namecount);
                outfile = fopen(outname, "w");
                fwrite(buffer, 1, 512, outfile);

            }
            else
            {
                fwrite(buffer, 1, 512, outfile);
            }
        }
    }

    //Closes infile
    fclose(inptr);

    //Frees buffer
    free(buffer);

    //If all went well
    return 0;

}