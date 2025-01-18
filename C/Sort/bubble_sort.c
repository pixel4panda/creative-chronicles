// Code in C that sorts an array through bubble sort
void bubble_sort (int random[])
{
    // Create swap counter
    int swapc;
    // Create a space to store value swapped
    int value;

    do
    {
        // Set swap counter to 0
        swapc = 0;
        // Remember size is reduce by 1 because I am looking at i and i + 1
        for (int i = 0; i < array_size - 1; i++)
        {
            // Compare pairs
            if (random[i + 1] < random[i])
            // NOTE: from smallest to largest. If you want to sort through decreasing order, invert operational
            {
                value = random[i];
                random[i] = random[i + 1];
                random [i + 1] = value;

                swapc++;
            }
        }
    }
    while (swapc != 0);
}
