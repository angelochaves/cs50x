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
    int contn = 0;
    unsigned char *buffer = malloc(sizeof(char) * 512);
    FILE *outfile = NULL;
    char outname[8];

    //Iterates to create next file name
    while (true)
    {
        //A new outfile will start to being copied
        if (contn == 1)
        {
            namecount++;
            sprintf(outname, "%03i.jpg", namecount);
            outfile = fopen(outname, "w");
            contn = 0;
        }
        //The first outfile is created and get set to receive data
        else
        {
            if (fread(buffer, 1, 512, inptr) == 0)
            {
                break;
            }
            else
            {
                sprintf(outname, "%03i.jpg", namecount);
                outfile = fopen(outname, "w");
            }
        }

        //Iterates to find the first signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fwrite(buffer, 1, 512, outfile);
            while (true)
            {
                if (fread(buffer, 1, 512, inptr) == 0)
                {
                    break;
                }
                else
                {
                    //If it finds another signature it means the beggining of a new file, so it breaks the loop
                    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                    {
                        fclose(outfile);
                        break;
                    }
                    //Otherwise, the outfile continues to being fed
                    else
                    {
                        fwrite(buffer, 1, 512, outfile);
                        contn = 1;
                    }
                }
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