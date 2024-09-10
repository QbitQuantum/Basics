void TreatVariations(char *fileName)
{
	char line[LineSize];	// pointer to the line read from the netlist file
	FILE *inputFd;			// file descriptor, used to access its contents
	
	if ((inputFd = fopen(fileName, "r")) == NULL) 
		perror("Failed to open file!");
	
	int numberOfLines = GetNumberOfLines(inputFd);	// counts the number of comment lines to set the size of the variables's vectors
	int indexVectorVariables = 0;					// vectorVariables' iterator
	int indexSteppedVariables = 0;					// steppedVariables' iterator
	
	int steppedVarsIndex = 0;
	int vectorVarsIndex = 0;
	
	int tempFilesIndex = 0;
	int tempFilesIndexHelper = 0;
	FILE *tempFiles[numberOfLines];
	
	VectorVariable vectorVariables[numberOfLines];			// vector for the vector variables
	SteppedVariable steppedVariables[numberOfLines];		// vector for the stepped variables
	
	while (fgets(line, LineSize, inputFd) != NULL)
	{
		if (strstr(strchr(line, '{'), ":") != NULL)
		{
			steppedVariables[indexSteppedVariables] = (SteppedVariable)
			{
				.preffix = "\0",
				.start = 0,
				.end = 0,
				.step = 0,
				.suffix = "\0"
			};
			
			GetRangeFromLine(line, &steppedVariables[indexSteppedVariables++]);
		}
		else
		{
			vectorVariables[indexVectorVariables] = (VectorVariable)
			{
				.preffix = "\0",
				.values = { "\0" },
				.suffix = "\0",
				.numberOfValues = 0
			};
			
			GetVectorFromLine(line, &vectorVariables[indexVectorVariables++]);
		}
	}
	
	if (fclose(inputFd))
		perror("Failed to close file!");
	
	while (vectorVarsIndex < indexVectorVariables)
	{
		tempFiles[tempFilesIndex++] = CreateVectorStructure(&vectorVariables[vectorVarsIndex]);
		vectorVarsIndex++;
	}
	
	while (steppedVarsIndex < indexSteppedVariables)
	{
		tempFiles[tempFilesIndex++] = CreateSteppedStructure(&steppedVariables[steppedVarsIndex]);
		steppedVarsIndex++;
	}
	
	int fileIsEmpty = 1;
	char outputFileName[strlen(fileName) + 10];		// sums the quantities of characters in the file name and in "_alters.sp"
	
	strcpy(outputFileName, fileName);
	strcat(outputFileName, "_alters.sp");
	
	while (tempFilesIndexHelper < tempFilesIndex)
	{
		FillOutFile(tempFiles[tempFilesIndexHelper++], outputFileName, fileIsEmpty);
		fileIsEmpty = 0;
	}
}