double exact_pull(int *pos)
{
    int i = 0;
    double d = 0.0, pull = 0.0;
    for (i = 0; i < MAX_NUMBER_OF_MOVES - NUM_MOVES_REMAINING; i++)
    {
        d = distance_squared(pos[0], pos[1], moves[i * 2], moves[i * 2 + 1]);
        if(d)
	{
            if (i % 2)
	        pull += (1.0 / d);
	    else
	        pull -= (1.0 / d);
	}
    }
    return pull;
}