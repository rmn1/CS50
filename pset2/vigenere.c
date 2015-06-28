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
    
    string key = argv[1];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("incorrect format");
            return 1;
        }
    }
    
    string plaintext = GetString();
    int letter_counter = 0;
    char tempc;
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        // if a-z / A-Z, encrypt
        {
            if (plaintext[i] >= 65 && plaintext[i] <= 90)
            // uppercase letters
            {
                if (islower(key[letter_counter % strlen(key)]))
                {
                    tempc = toupper(key[letter_counter % strlen(key)]);
                    printf("%c", (plaintext[i] - 65 + tempc - 65) % 26 + 65);
                }
                else
                {
                    printf("%c", (plaintext[i] - 65 + key[letter_counter % strlen(key)] - 65) % 26 + 65);
                }
            }
            else
            // lowercase letters (97 <= x <= 122)
            { 
                if (isupper(key[letter_counter % strlen(key)]))
                {
                    tempc = tolower(key[letter_counter % strlen(key)]);
                    printf("%c", (plaintext[i] - 97 + tempc - 97) % 26 + 97);
                }
                else
                {
                    printf("%c", (plaintext[i] - 97 + key[letter_counter % strlen(key)] - 97) % 26 + 97);
                }
            }
            letter_counter++; // increase count to proceed within key (note the mod ref to key position above
        }
        else
        // if not a-z, just reprint character
        {
            printf("%c", plaintext[i]);
        }   
    }
    printf("\n");
    return 0;
}
