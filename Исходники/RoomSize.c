int main()
{
	int t, row, col, i, j, count = 0;
	unsigned char **Room;
	unsigned char temp;
	FILE *fp;
	fp = fopen("input.txt", "r");
	if (fp == NULL) return 0; /* start FILE IO */
	fscanf(fp, "%d", &t); /* read Data Number */
	while (t--)
	{
		fscanf(fp, "%d %d", &col, &row); /* read Data */
		Room = (unsigned char**)malloc(sizeof(unsigned char*)*row); /* read Room data */
		for (i = 0; i < row; i++)
			Room[i] = (unsigned char*)malloc(sizeof(unsigned char)*(col));
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				fscanf(fp, "%c", &temp);
				while ((temp != '.') && (temp != '+')) fscanf(fp, "%c", &temp);
				Room[i][j] = temp;
			}
		}
		for (i = 1; i < row-1; i++) for (j = 0; j < col; j++) if (Room[i][j] == '.') count += floodFill(Room, i, j, '.', '+', &count); /* figure out result */		
		printf("%d\n", count); /* print output */
		Sorting(roomSIZE, 0, count);
		for (i = 0; i < count; i++)
			printf("%d ", roomSIZE[i]);
		printf("\n");
		for (i = 0; i < row; i++) /* initialize Room memory */
		{
			free(Room[i]);
			Room[i] = NULL;
		}
		free(Room);
		Room = NULL;
		for (i = 0; i < count; i++) roomSIZE[i] = 0; /* initialize roomsize */
		count = 0; /* initialize room counter */
	}
	fclose(fp); /* close FILE IO */
	return 1;
}