/****************************************************************************
 * mario.c
 *
 * Computer Science 50
 * Problem Set 1 - Hacker Edition
 *
 * Draw double mario-style pyramids with hash-marks.
 ***************************************************************************/

#include <stdio.h>

int main(void)
{
    // prompt user to enter height and verify response is non-negative number <= 23
    int height = 0;
    int j;

    do {
        printf("Enter desired height of pyramid (2 > h > 23): ");
        scanf ("%d", &height);
        if (height == 0) return 0;
        
    } while (height > 23 || height < 1); 
    
    // loop through lines of the pyramid
    for (int i = 0; i < height; i++)
    {
        // print spaces to left of pyramind (no need for any on the right) 
        for (j = height-i-1; j--; printf(" "));
        
        //print left-hand pyramid
        for (j = i+1; j--; printf("#"));
        
        // print gap between pyramids
        printf("  ");
        
        //print right-hand pyramid
        for (j = i+1; j--; printf("#"));
        
        printf("\n");
    }  
    return 0;
}