#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
    
int main(int argc, string argv[])
{
    //Tests for argument number and argument 1 as null
    if (argc != 2 || argv[1] == '\0')
    {
        printf("\nUsage: ./crack hash\n\n");
        return 1;
    }
    else
    {
        string guess;
        char salt[2];
        char tp[5] = "";

        //Get salt value from inputed hash
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];

        //Nested loops to iterate every combination
        for (int m = 0; m < 123; m++)
        {
            for (int l = 0; l < 123; l++)
            {
                for (int k = 0; k < 123; k++)
                {
                    for (int j = 0; j < 123; j++)
                    {
                        for (int i = 65; i < 123; i++)
                        {
                            tp[0] = i;
                            tp[1] = j;
                            tp[2] = k;
                            tp[3] = l;
                            tp[4] = m;

                            i = (i == 90) ? 96 : i;

                            //printf("%s\n", tp);
                            guess = crypt(tp, salt);
                            //printf("%s\n", guess);
                            
                            //Compares the hashed iteration with actual hash
                            if (strcmp(guess, argv[1]) == 0)
                            {
                                printf("%s\n", tp);
                                return 0;
                            }
                        }
                        //Forces the first value of second digit to be null
                        j = (j == 0) ? 64 : j;
                        //Makes the iteration to jump over values 91 to 97 (non alphabetic)
                        j = (j == 90) ? 96 : j;
                    }
                    k = (k == 0) ? 64 : k;
                    k = (k == 90) ? 96 : k;
                }
                l = (l == 0) ? 64 : l;
                l = (l == 90) ? 96 : l;
            }
            m = (m == 0) ? 64 : m;
            m = (m == 90) ? 96 : m;
        }
        return 1;
    }
}

