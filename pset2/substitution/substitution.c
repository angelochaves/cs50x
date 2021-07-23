#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{

    //Tests for null argument 1
    if (argv[1] == '\0')
    {
        printf("\nUsage: ./substitution key\n\n");
        return 1;
    }

    //Tests if there is 26 alphabetic characters
    if (argc == 2 && strlen(argv[1]) == 26)
    {
        char alpha[26];
        for (int i = 0; i < 26; i++)
        {
            for (int j = i + 1; j < strlen(argv[1]); j++)
            {
                // Test for alphabetic and non-duplcated input
                if ((isalpha(argv[1][i])) && (argv[1][i] != argv[1][j]))
                {
                    continue;
                }
                else
                {
                    printf("\nKey must contain non-duplicated alphabetic characters only.\n\n");
                    return 1;
                }
            }

            // Copy alphabet to an array
            alpha[i] = (char)(i + 97);
        }

        //Lowercase key
        char key[26];
        int k = 0;
        for (int i = 0; i < 26; i++)
        {
            key[i] = tolower(argv[1][k]);
            k++;
        }

        //Prompts user for a plaintext
        string ptext = get_string("plaintext: ");
        // Alocate memory for a string to receive same values of ptext
        char *ctext = malloc(sizeof(char) * strlen(ptext));

        for (int i = 0; i < strlen(ptext); i++)
        {
            ctext[i] = ptext[i];
        }

        for (int i = 0; i < strlen(ctext); i++)
        {
            ctext[i] = tolower(ctext[i]);
        }

        //Ciphers the plaintext
        for (int i = 0; i < strlen(ctext); i++)
        {
            for (int j = 0; j < strlen(alpha); j++)
            {
                if (ctext[i] == alpha[j])
                {
                    ctext[i] = key[j];
                    break;
                }
            }
        }

        // Recompose uppercase
        for (int i = 0; i < strlen(ctext); i++)
        {
            if (isupper(ptext[i]))
            {
                ctext[i] = toupper(ctext[i]);
            }
        }

        printf("ciphertext: %s\n\n", ctext);

        free(ctext);
        return 0;

    }
    else
    {
        printf("\nKey must contain 26 characters.\n\n");
        return 1;
    }
}