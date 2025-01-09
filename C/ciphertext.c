// This was an assignment to write a program to create ciphertext out of a 26 digit alphabetical key
// Example usage: ./ciphertext NQXPOMAFTRHLZGECYJIUWSKDVB

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int const K = 26;
char ABC[K] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
               'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int alphabetical_array(string array);
void error(void);
int repeat_argument(string array);
char rotate_char(string key, char c);
int main(int argc, string argv[])
{
    // Make sure only a single command argument is being used
    if (argc != 2)
    {
        error();
        return 1;
    }

    // Make sure my key is valid
    // Key has not 26 characters
    int klength = strlen(argv[1]);
    if (klength != K)
    {
        error();
        return 1;
    }
    // Key has non alphabetic characters
    else if (alphabetical_array(argv[1]) == 0)
    {
        error();
        return 1;
    }
    // Key has repetead characters
    else if (repeat_argument(argv[1]) == 0)
    {
        error();
        return 1;
    }

    // Correct key to upper case
    for (int i = 0; i < K; i++)
    {
        argv[1][i] = toupper(argv[1][i]);
    }

    // Ask user to input plaintext
    string ptext = get_string("plaintext: ");
    string ctext = ptext;

    // Convert plain text to cipher
    for (int j = 0, slength = strlen(ptext); j < slength; j++)
    {
        if (islower(ptext[j]) != 0)
        {
            ctext[j] = tolower(rotate_char(argv[1], ptext[j]));
        }
        else if (isupper(ptext[j]) != 0)
        {
            ctext[j] = rotate_char(argv[1], ptext[j]);
        }
    }

    // Print ciphertext
    printf("ciphertext: %s\n", ctext);
}

int alphabetical_array(string array)
{
    for (int i = 0, length = strlen(array); i < length; i++)
    {
        if (isalpha(array[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void error(void)
{
    printf("Error. Usage: ./substitution 26_alphabetical_key\n");
}

int repeat_argument(string array)
{
    int length = strlen(array);
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] == array[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

char rotate_char(string key, char c)
{
    // Find char in the alphabet
    c = toupper(c);
    int pos = 0;
    for (int i = 0; i < K; i++)
    {
        if (c == ABC[i])
        {
            pos = i;
        }
    }

    // Replace char with corresponding cipher
    c = key[pos];
    return c;
}
