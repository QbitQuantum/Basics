int main(void)
{
	FILE* file;
	int error = fopen_s(&file, FILENAME, "w+");
	uint32_t random;
	size_t i;
	for (i = 0; i < SIZE; i++)
	{
		while (rand_s(&random))
		{ }
		fwrite(&random, sizeof(random), 1, file);
	}
	_fcloseall();
	return 0;
}