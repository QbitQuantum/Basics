/*
*	Reads a scoring matrix from the specified file.
*
*	File should be of the following format:
*
*	A	3	-2	-1	-2
*	C	-2	3	-2	-1
*	G	-1	-2	3	-2
*	T	-2	-1	-2	3
*
*	Returns the scoring matrix as a ScoringMatrix struct containting the scoring matrix,
*	a lookup table for indexing into the matrix, and a reverse lookup table for converting
*	the numerical index back to a char.
*/
ScoringMatrix* read_scoring_file(char* scoreFile)
{
	ScoringMatrix* scoring = malloc(sizeof(ScoringMatrix));
	scoring->numChars = 0;
	
	char line[256];
	char* temp;
	int lineLength;
	int numLines = 0;
	int i;
	int j;
	
	FILE* file = fopen(scoreFile, "r");
	
	if (fgets(line, 256, file) != NULL)
	{
		strtok(line, " 	\t\n");
		
		while (strtok(NULL, " 	\t\n") != NULL)
		{
			scoring->numChars++;
		}
	} else
	{
		printf("Unable to read from score file. Exiting.\n");
		exit(1);
	}
	
	rewind(file);
	
	scoring->matrix = malloc(sizeof(int) * (scoring->numChars) * (scoring->numChars));
	scoring->lookupTable = malloc( sizeof(char) * 128 );
	memset(scoring->lookupTable, -1, sizeof(char) * 128);
	
	// setup characters to ignore: space, tab, carriage return, and newline
	scoring->lookupTable[' '] = scoring->lookupTable['\t'] = scoring->lookupTable['\r'] = scoring->lookupTable['\n'] = -19;

	scoring->lookupTableReverse = malloc (sizeof(char) * (scoring->numChars));
	
	for (i = 0; i < scoring->numChars; i++)
	{
		fgets(line, 256, file);

		temp = strtok(line, " \t\n");

		j = 0;
		scoring->lookupTable[temp[0]] = i;
		scoring->lookupTable[temp[0] ^ 32 ] = i;
		
		scoring->lookupTableReverse[i] = temp[0];
		
		while (((temp = strtok(NULL, " \t\n")) != NULL) && j <= scoring->numChars)
		{
			scoring->matrix[ i * (scoring->numChars) + j++] = atoi(temp);
		}
	}

	fclose(file);

	return scoring;
}