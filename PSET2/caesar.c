#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void fail(string program, string error);
char lower(char c, int key);
char upper(char c, int key);

int main(int argc, string argv[])
{
    // Check if key input present, call fail if not
    if (argc != 2)
    {
        fail(argv[0], "key");
        return 1;
    }

    // Check key is numeric value > 0, call fail if not
    int key = atoi(argv[1]);
    if (key == 0)
    {
        fail(argv[0], "key");
        return 1;
    }

    // Valid key entered
    else
    {
        // Set key, get plaintext & it's string length
        key = key % 26;
        string ptext = get_string("plaintext:  ");
        printf("ciphertext: ");
        int ptext_len = strlen(ptext);

        // Iterate over each char in plaintext
        for (int i = 0; i < ptext_len; i++)
        {
            char c = ptext[i];
            char cipher_char = c;

            // Check if char upper/lower case letter
            if (c >= 97 && c <= 122)
            {
                cipher_char = lower(c, key);
            }
            else if (c >= 65 && c <= 90)
            {
                cipher_char = upper(c, key);
            }

            // Print encrypted letter
            printf("%c", cipher_char);
        }

        // Complete - new line for prompt
        printf("\n");
        return 0;
    }
}

// Display error - pass prog name & error type
void fail(string program, string error)
{
    printf("Usage: %s %s\n", program, error);
}

// Encrypt lower case letter - pass letter & key
char lower(char c, int key)
{
    // Encryption moves beyond "z"
    if (c + key > 122)
    {
        return c - 26 + key;
    }
    // Encryption doesn't move beyond "z"
    else
    {
        return c + key;
    }
}

// Encrypt upper case letter - pass letter & key
char upper(char c, int key)
{
    // Encryption moves beyond "Z"
    if (c + key > 90)
    {
        return c - 26 + key;
    }
    // Encryption doesn't move beyond "z"
    else
    {
        return c + key;
    }
}
