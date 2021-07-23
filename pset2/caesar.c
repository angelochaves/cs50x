#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    //validates arguments input
    if (argc == 2 && atoi(argv[1]) != 0)
    {
        printf("Success\n");
        //printf("%i\n\n", atoi(argv[1]));
    }
    else
    {
        printf("\nUsage: ./caesar key\n\n");
        return 1;
    }
    
    int key = atoi(argv[1]);
    
    while (key > 26)
    {
        key = key - 26;
    }
    
    //Prompts user for a plaintext
    string ptext = get_string("plaintext:  ");
    string ctext = ptext;
    
    //Ciphers the plaintext
    for (int i = 0, n = strlen(ctext); i < n; i++)
    {
        if (ctext[i] >= 'A' && ctext[i] <= 'Z')
        {
            if (ctext[i] + key > 90)
            {
                ctext[i] = (65 - 1) + key - (90 - ctext[i]);
            }
            else
            {
                ctext[i] += key;
            }
        }
        else
        {
            if (ctext[i] >= 'a' && ctext[i] <= 'z')
            {
                if (ctext[i] + key > 122)
                {
                    ctext[i] = (97 - 1) + key - (122 - ctext[i]);
                }
                else
                {
                    ctext[i] += key;
                }
            }
        }
    }
    
    printf("\nciphertext: %s\n\n", ctext);
}
