#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // confirm user has entered only two argument (program name and key)
    if (argc != 2)
    {
        printf("NO!");
        return 1;
    }
       
    int key = atoi(argv[1]);
    
    // get key from user and convert to integer
    string plaintext = GetString();
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            // encrypt uppercase letters
            if (plaintext[i] >= 65 && plaintext[i] <= 90)
            {
                printf("%c", (plaintext[i] - 65 + key) % 26 + 65);
            }
            
            // encrypt lowercase letters
            if (plaintext[i] >= 97 && plaintext[i] <= 122)
            {
                printf("%c", (plaintext[i] - 97 + key) % 26 + 97);
            }
        }
        // if not a-z, just reprint character
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
