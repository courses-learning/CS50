#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void fail(string program, string error);
int shift(char c);
char lower(char c, int key);
char upper(char c, int key);

int main(int argc, string argv[])
{
    // Check if key input present, call fail if not
    if (argc != 2)
    {
        fail(argv[0], "keyword");
        return 1;
    }

    // Check key is alpha value, call fail if not
    int key_len = strlen(argv[1]);
    for (int i = 0; i < key_len; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            fail(argv[0], "keyword");
            return 1;
        }
    }

    // Valid key entered get plaintext & it's string length
    string ptext = get_string("plaintext:  ");
    printf("ciphertext: ");
    int ptext_len = strlen(ptext);



    // Iterate over each char in plaintext
    for (int j = 0, i = 0; i < ptext_len; i++)
    {
        int key = shift(argv[1][j]);
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

        // Next key only if previous char was alpha
        if (isalpha(ptext[i]) == 0)
        {
            continue;
        }
        else if (j < key_len - 1)
        {
            j++;
        }
        else
        {
            j = 0;
        }
    }

    // Success - new line for prompt
    printf("\n");
    return 0;
}

// Display error - pass prog name & error type
void fail(string program, string error)
{
    printf("Usage: %s %s\n", program, error);
}

// Return shift no from key char
int shift(char c)
{
    if (c >= 97 && c <= 122)
    {
        return (c - 97);
    }
    else if (c >= 65 && c <= 90)
    {
        return (c - 65);
    }
    else
    {
        return 0;
    }
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
