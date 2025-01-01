

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Score chart
int CHART[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int score(string word);
string upper_word(string word);
int main(void)
{
    // Player inputs
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Transform all to uppercase
    player1 = upper_word(player1);
    player2 = upper_word(player2);

    // Calculate scores
    int score1 = score(player1);
    int score2 = score(player2);

    // Return winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

// How many points per word
int score(string word)
{
    // Initialize score
    int points = 0;

    // Analyze each character
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        // Invalid char
        if (word[i] > 'Z' || word[i] < 'A')
        {
            points += 0;
        }
        // Valid char
        else
        {
            int a = word[i] - 'A';
            points += CHART[a];
        }
    }
    return points;
}

// Capitalize words
string upper_word(string word)
{
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        word[i] = toupper(word[i]);
    }
    return word;
}
