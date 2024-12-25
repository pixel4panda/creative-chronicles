// Write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid AmericanExpress, MasterCard, or Visa card number, 
// per the definitions of each’s format herein. So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n 
// or VISA\n or INVALID\n, nothing more, nothing less. 

#include <cs50.h>
#include <stdio.h>

int get_digit(long number, int size, int position);
void results(int eval, string text);
int validation(long number, int size);
int main(void)
{
    // Get card number
    long card_number;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    // Get the number of digits in the card
    long control = card_number;
    int digits = 0;
    while (control > 0)
    {
        control = control / 10;
        digits++;
    }

    // Check card
    int valid;
    string card_type;
    int firstd = get_digit(card_number, digits, 1);
    int secondd = get_digit(card_number, digits, 2);

    // Amex (15 digits, 34 or 37 start)
    if (digits == 15 && firstd == 3 && (secondd == 4 || secondd == 7))
    {
        valid = validation(card_number, digits);
        card_type = "AMEX";
        results(valid, card_type);
    }
    // Visa (13 digits, 4 start)
    else if (digits == 13 && firstd == 4)
    {
        valid = validation(card_number, digits);
        card_type = "VISA";
        results(valid, card_type);
    }
    // Mastercard and Visa (16 digits)
    else if (digits == 16)
    {
        // Mastercard (51 to 55 starts)
        if (firstd == 5 && (secondd >= 1 && secondd <= 5))
        {
            valid = validation(card_number, digits);
            card_type = "MASTERCARD";
            results(valid, card_type);
        }
        // Visa (4 start)
        else if (firstd == 4)
        {
            valid = validation(card_number, digits);
            card_type = "VISA";
            results(valid, card_type);
        }
        else
        {
            valid = 1;
            card_type = "NOPE";
            results(valid, card_type);
        }
    }
    else
    {
        valid = 1;
        card_type = "NOPE";
        results(valid, card_type);
    }
}

// Find a POSITION digit inside the NUMBER of certain SIZE
int get_digit(long number, int size, int position)
{
    int answer;
    for (int i = size; i >= position; i--)
    {
        answer = number % 10;
        number = (number - answer) / 10;
    }
    return answer;
}

// Prints card type, or invalid
void results(int eval, string text)
{
    if (eval == 0)
    {
        printf("%s\n", text);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Checks if the card is valid
int validation(long number, int size)
{
    // Multiply every other digit by 2 and sum
    int step_one = 0;
    int times_two;
    for (int i = size - 1; i > 0; i = i - 2)
    {
        times_two = get_digit(number, size, i) * 2;
        if (times_two > 9)
        {
            times_two = get_digit(times_two, 2, 2) + get_digit(times_two, 2, 1);
        }
        step_one = step_one + times_two;
    }

    // Add numbers not multiplied
    int step_two = 0;
    for (int i = size; i > 0; i = i - 2)
    {
        step_two = step_two + get_digit(number, size, i);
    }

    // Add the 2 sums and check if divisible by 10
    int verify = (step_one + step_two) % 10;
    return verify;
}
