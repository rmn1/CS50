/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // return false if number to be found is negative
    if (value < 0)
        return false;
    
    // binary search - iterative
    int left = 0;
    int right = n;
    int middle = (left + right)/2;
    while (left <= right)
    {
        if (value == values[middle])
            return true;
        if (values[middle] < value)
            left = middle + 1;
        else
            right = middle - 1;
        middle = (left + right) / 2;
    }
    
   return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // SELECTION SORT
    int temp, min_index;
    for (int i = 0; i <= n-1; i++)
    {
        min_index = i;
        for (int j = i+1; j <= n; j++)
        {
            if (values[j] < values[min_index])
                min_index = j;
            temp = values[i];
            values[i] = values[min_index];
            values[min_index] = temp;
        }
    }
    
    return;
}
