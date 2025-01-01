// Assignment to create a mirrored pyramid out of #
// Goal:
//     #  #
//    ##  ##
//   ###  ###

#include <cs50.h>
#include <stdio.h>

void pyramid_row(int length, int spc, int mid1, int mid2);
int main(void)
{
    // Get pyramid height 8# max
    int height;
    do
    {
        height = get_int("Pyramid height(1 to 8): ");
    }
    while (height < 1 || height > 8);

    // Defining how many columns
    int width = (height * 2) + 2;

    // Find the middle
    int middle1 = width / 2 - 1;
    int middle2 = width / 2;

    // Building the pyramid
    int spaces;
    for (int i = 0; i < height; i++)
    {
        spaces = height - 1 - i;
        pyramid_row(width, spaces, middle1, middle2);
    }
}

// Print row of pyramid
void pyramid_row(int length, int spc, int mid1, int mid2)
{
    int stop;
    for (int i = 0; i < length; i++)
    {
        stop = length - spc;
        if (i < spc)
        {
            printf(" ");
        }
        else if (i == mid1 || i == mid2)
        {
            printf(" ");
        }
        else if (i < stop)
        {
            printf("#");
        }
    }
    printf("\n");
}
