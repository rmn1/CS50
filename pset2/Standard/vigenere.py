'''
* Vigenère’s cipher: encrypts only alphabetical characters
*
* Python implementation of program written in C
* as a solution to a problem set for Harvard CS50 on edX
'''

# -*- coding: utf-8 -*-
import sys

def validate_key():
    # confirm exactly two arguments entered on command line (program name and keyword)
    if len(sys.argv) != 2:
        print("Incorrect usage. Usage: python vigenere <key>")
        return False

    # assign keyword to 'key' variable and validate format (alpha chars only)
    if not (sys.argv[1]).isalpha:
        print("Invalid key. Use only alphabetical characters.")
        return False
    else:
        return sys.argv[1]

def encrypt(plaintext, key):
    output = ''
    key_len = len(key)
    letter_counter = 0

    # loop through plaintext, char by char, encrypting using keyword provided by user
    for c in plaintext:
        # isalpha() include whitespace, second condition prints whitespace without encryption
        if not c.isalpha() or c.isspace():
            output += c

        else:
            # encrypt uppercase letter of plaintext
            # if current keyword char is lowercase, refer to uppercase counterpart
            if c.isupper():
                # refer to current char in keyword, by cycling through using mod and length of keyword
                cipher_char = key[letter_counter % key_len].upper()
                cipher_char_ascii = ord(cipher_char.upper()) if cipher_char.islower() else ord(cipher_char)
                output += chr(((ord(c) - ord('A')) + (cipher_char_ascii - ord('A'))) % 26 + ord('A'))

            # encrypt lowercase letters in plaintext
            # refer to lowercase counterpart if current keyword char is uppercase
            else:
                cipher_char = key[letter_counter % key_len]
                cipher_char_ascii = ord(cipher_char.lower()) if cipher_char.isupper() else ord(cipher_char)
                output += chr(((ord(c) - ord('a')) + (cipher_char_ascii - ord('a'))) % 26 + ord('a'))

            # advance position in keyword to next char
            letter_counter += 1

    return output

if __name__ == '__main__':
    key = validate_key()
    if not key:
        sys.exit(0)

    plaintext = raw_input("Enter text to be encrypted: ")
    encrypted = encrypt(plaintext, key)
    print('Encrypting "' + plaintext + '" with a keyword of "' + key + '," using Vigenère’s cipher, yields the ciphertext "' + encrypted + '."')