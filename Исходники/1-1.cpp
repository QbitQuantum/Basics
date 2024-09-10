void generate_data(double array[], size_t array_len,
                   int upper_bound)
{
    size_t i;
    // Set seed to 1
    srand(1);
    // Generate random numbers between 0 and upper_bound
    for(i = 0; i < array_len; i++)
    {
        array[i] = rand() % upper_bound;
    }
}