#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    //Tests for alphabetic argument
    
    int alphainput = 0, key = 0, j = 0;
    
    //Tests for null argument 1
    if (argv[1] == '\0')
    {
        printf("\nUsage: ./vigenere keyword\n\n");
        return 1;
    }
    
    //Tests if every character is alphabetic
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        alphainput = (tolower(argv[1][i]) < 'a' || tolower(argv[1][i]) > 'z') ? 1 : 0;
    }
         
    //validates arguments input
    if (argc == 2 && alphainput == 0)
    {
        printf("Success\n");
    }
    else
    {
        printf("\nUsage: ./vigenere keyword\n\n");
        return 1;
    }
    
    //Prompts user for a plaintext
    string ptext = get_string("plaintext:  ");
    string ctext = ptext;
        
    //Ciphers the plaintext
    for (int i = 0, n = strlen(ctext); i < n; i++)
    {
        //Tests and reinitiates value of keyword
        j = (j >= strlen(argv[1])) ? 0 : j;
        //Call function to shift the value of the key
        key = shift(tolower(argv[1][j]));
        
        //Ciphers the plaintext
        if (ctext[i] >= 'A' && ctext[i] <= 'Z')
        {
            if (ctext[i] + key > 90)
            {
                ctext[i] = (65 - 1) + key - (90 - ctext[i]);
                j++;
            }
            else
            {
                ctext[i] += key;
                j++;
            }
        }
        else
        {
            if (ctext[i] >= 'a' && ctext[i] <= 'z')
            {
                if (ctext[i] + key > 122)
                {
                    ctext[i] = (97 - 1) + key - (122 - ctext[i]);
                    j++;
                }
                else
                {
                    ctext[i] += key;
                    j++;
                }
            }
        }
    }
    
    printf("\nciphertext: %s\n\n", ctext);
}

//Attributes values from 0 to 25 to the alphabet instead of ASCII values
int shift(char c)
{
    return (c - 97);
}

