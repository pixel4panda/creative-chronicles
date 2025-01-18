// Code in C for a function that sorts an array through selection sort
void selection_sort (int random[])
{
    int min;
    int pos;

    // Define elements I am comparing
    // from position 0 to size, then from 1 to size ...
    for (int i = 0; i < array_size; i++)
    {
        min = random[i];
        pos = i;
        // Find the smallest element
        for (int j = i; j < array_size; j++)
        {
            if (random[j] < min)
            {
                min = random[j];
                pos = j;
            }
        }
        // Swap its place with the first element
        random[pos] = random[i];
        random[i] = min;
    }
}
