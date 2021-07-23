#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    int quarter, dime, nickel, penny, coins;
    float change;

    //Gets the value of change as float >0 only
    do
    {
        change = get_float("Change owed: ");
    }
    while (change <= 0);

    //Converts dollars to cents to avoid float imprecision
    int owed = round(change * 100);
    
    //Gets the maximum number of quarters by the integer part of the division
    quarter = owed / 25;
    //Now, the change owed is just the real part of the division
    owed = owed % 25;
    
    //Gets the maximum number of dimes by the integer part of the division
    dime = owed / 10;
    //Now, the change owed is just the real part of the division
    owed = owed % 10;
    
    //Gets the maximum number of nickels by the integer part of the division
    nickel = owed / 5;
    //Now, the change owed is just the real part of the division
    owed = owed % 5;
    
    //Remaining change as pennies
    penny = owed;

    coins = quarter + dime + nickel + penny;

    printf("\nThe minimal number of coins are: %i\n\n", coins);
    printf("Being: %i quarter(s), %i dime(s), %i nickel(s) and %i penny(ies)\n\n", quarter, dime, nickel, penny);
}

