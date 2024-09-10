int *line_segments_generation()
{
	int *lines = new int[LINE_NUM*4];

	srand(time(0));

	for (int i = 0; i < LINE_NUM; i++) {
		lines[4*i] = rand() % W;
		lines[4*i + 1] = rand() % H;
		lines[4*i + 2] = rand() % W;
		lines[4*i + 3] = rand() % H;
	}

	return lines;
}