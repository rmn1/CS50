/****************************************************************************
 * vigenere_non_cs50.c
 *
 * Computer Science 50
 * Problem Set 2
 *
 * Implementation of Vigenère’s cipher without using the CS50 library
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // confirm user has entered exactly two arguments (program name and keyword)
    if (argc != 2)
    {
        printf("Incorrect usage. Usage: ./vigenere <key>\n");
        return 1;
    }

    // assign keyword to 'key' variable and validate format (alpha chars only)
    char* key = argv[1];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Invalid keyword. Use only alphabetical characters.\n");
            return 1;
        }
    }

    // read plaintext to be encrypted from user, limited to 100 characters
    int bytes_read = -1;
    size_t nbytes = 100;
    char* plaintext = (char*) malloc(nbytes+1);
    while (bytes_read <= 0)
    {
        printf("Please enter text to be encrypted, up to 100 characters long: ");
        bytes_read = getline(&plaintext, &nbytes, stdin);
        if (bytes_read <= 0)
        {
            printf("Error.\n");
        }
    }

    unsigned long text_len = strlen(plaintext);
    char encrypted[text_len];
    plaintext[text_len-1] = '\0';
    encrypted[text_len] = '\0';

    int letter_counter = 0;
    char tempc;
    for (int i = 0; i < text_len; i++)
    {
        // if current char is a-z / A-Z, encrypt
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                // capital / uppercase letters
                // if pointing to lowercase char in keyword, encrypt using uppercase counterpart
                if (islower(key[letter_counter % strlen(key)]))
                {
                    tempc = toupper(key[letter_counter % strlen(key)]);
                    encrypted[i] = ( ((plaintext[i] - 'A') + (tempc - 'A')) % 26 ) + 'A';
                }
                else
                {
                    encrypted[i] = ( ((plaintext[i] - 'A') + (key[letter_counter % strlen(key)] - 'A')) % 26) + 'A';
                }
            }
            else
            {
                //lowercase letters
                // if pointer to uppercase char in keyword, encrypt using lowercase counterpart
                if (isupper(key[letter_counter % strlen(key)]))
                {
                    tempc = tolower(key[letter_counter % strlen(key)]);
                    encrypted[i] = ( ((plaintext[i] - 'a') + (tempc - 'a')) % 26 ) + 'a';
                }
                else
                {
                    encrypted[i] = ( ((plaintext[i] - 'a') + (key[letter_counter % strlen(key)] - 'a')) % 26) + 'a';
                }
            }
            // advance pointer to character in keyword, but not for non-alpha chars in plaintext
            letter_counter++;
        }
        // if non-alpha character, simply append plaintext without encryption
        else
        {
            encrypted[i] = plaintext[i];
        }
    }
    printf("Encrypting \"%s\" with a keyword of \"%s\", using Vigenère’s cipher, yields the ciphertext \"%s\".\n", plaintext, key, encrypted);
    free(plaintext);
    return 0;
}
