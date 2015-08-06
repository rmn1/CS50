/****************************************************************************
 * initials.c
 *
 * Computer Science 50
 * Problem Set 2 - Hacker Edition
 *
 * Return uppercase initials of name provided.
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
int main(void)
{
    // get name from user
    printf("Enter name: ");
    char* name = malloc(128*sizeof(char));
    fgets (name, 128, stdin);

    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ' ')
        {
            while (name[i] == ' ')
                i++;
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
}