#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    int card[16];
    int digits = 0, size = 0, sum = 0;
    long int number;
    
    do
    {
        number = get_long("Please insert credit card number: ");
    }
    while (number < 0);
    
    //This block determines the lenght of credit card number
    long int counter = number;
    while (counter != 0)
    {
        counter = counter / 10;
        size++;
    }
    switch (size)
    {
        case 13:
            digits = 3;
            break;
            
        case 15:
            digits = 1;
            break;
            
        case 16:
            digits = 0;
            break;
            
        default:
            printf("ERROR! Non-valid number.");
    } printf("\n\nsize: %i and digits: %i\n\n", size, digits);
    
    for (int i = (15 - digits); i >= 0; i--)
    {
        card[i] = number % 10;
        number = number / 10;
    }

    printf("\n");
    
    //1st step for validation: Multiplication by 2
    for (int i = (14 - digits); i >= 0; i -= 2)
    {
        sum = sum + (card[i] * 2 / 10) + ((card[i] * 2) % 10);
    }
    printf("1st step validation: %i\n\n", sum);
    
    //2nd step for validation: checksum with final 0
    for (int i = (15 - digits); i >= 0; i -= 2)
    {
        sum = sum + card[i];
    }
    printf("2nd step validation: %i\n\n", sum);
    
    if ((sum % 10) != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (card[0] == 4)
        {
            printf("VISA\n");
        }
        else if (card[0] == 5)
        {
            if (card[1] == 1 || card[1] == 2 || card[1] == 3 || card[1] == 4 || card[1] == 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (card[0] == 3)
        {
            if (card[1] == 4 || card[1] == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
