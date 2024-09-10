int get_random(int low, int high)
{
	srand(clock());
	return low + (rand() % (high - low + 1));
}