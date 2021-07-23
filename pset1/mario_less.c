#include <stdio.h>
#include <string.h>

int main(void)
{
    char hash[8] = "#";
    char space[8] = "";
    int height, counter;
    
    //This block asks for a height to build the pyramid,
    //but it only accepts integers from 1 to 8, inclusive.
    //Otherwise, it will keep asking for a valid integer.
    do
    {
        height = get_int("Please choose height of pyramid: ");
    }
    while (height < 1 || height > 8);
    
    counter = height - 1;
    
    for (int i = 0; i < height; i++)
    {
        //This block adds a certain number os spaces,
        //according to the height of the pyramid,
        //in order to push the hashes to the right.
        for (int j = 0; j < counter; j++)
        {
            strcat(space, " ");
        }    
        //Then, this block concatenates the spaces
        //to the hashes in a way that both complement each
        //other 
        printf("%s%s\n", space, hash);
        strcat(hash, "#");
        strcpy(space, "");
        counter--;
    }
}

