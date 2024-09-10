void main(int argc, TCHAR *argv[])
{
	FILE	*fd = NULL; // The inputted list of scenarios to examine.
	HANDLE	 hd = NULL;		 // Handle to scenarios.
	TCHAR	 szCmdPmtPath[SIZE_256];
	TCHAR	 szCmdPmtInputFileName[SIZE_256];
	TCHAR	 szCmdPmtInputTitleName[SIZE_128];
	DWORD	 pathLength;
	C3mbStaticsLib staticLib;
	int		 numLineConverstions;
	int		 lineNumber;
	int		 i;
	BOOL	 generateNew;
	BOOL	 aeOn = FALSE;
	BOOL	 deleteOuputFile = FALSE;
	TCHAR	 szBuffer[SIZE_256];
	TCHAR	 szLine[SIZE_256];

	TCHAR	 szScenarioFileName[SIZE_128];

	TCHAR	 szSwitch[NUMVALIDSWITCHES][SIZE_16];

	double aeDb;
	BOOL  aeCycleOn;


	//----------------------------------------------------------------------------------//
	// Print Banner
	//-------------//
	printf("3MBS Verfication Application ver %3.1f\n\n", MMMBS_VERFICTN_APP_VER);
	if(argc < 2)
	{
		printf("Missing input file name containing list of scenarios to examine\n\n");
		printf("Usage: 3MBSValidation [listfile.txt]\n");
		Sleep(5000);
		return;
	}

	strncpy_s(szCmdPmtInputFileName,			// Destination buffer
		TCHARBFLEN(szCmdPmtInputFileName),	// Length of the destination bufffer
		argv[1],								// String to be copied
		TCHARBFLEN(szCmdPmtInputFileName));	// Max count

	staticLib.GetPathAndFileTitleFromFileName(szCmdPmtInputFileName,					// Inputted file name
									szCmdPmtPath,							// Buffer for file path
									TCHARBFLEN(szCmdPmtPath),				// Length of the file path buffer
									szCmdPmtInputTitleName,					// Buffer for file title
									TCHARBFLEN(szCmdPmtInputTitleName));	// Length of the file title buffer

	// Set the path if one was specified.  Otherwise, get the current directory.
	if((strlen(szCmdPmtPath) > 0) && (FALSE == SetCurrentDirectory(szCmdPmtPath)))
	{
		printf("Invalid path (%s) specified in input: %s\n", szCmdPmtPath, szCmdPmtInputFileName);
		Sleep(5000);
		return;
	}
	else
	{
		pathLength = GetCurrentDirectory(SIZE_256, szCmdPmtPath);
		if(pathLength == 0 || pathLength > SIZE_256)
		{
			printf("Current directory is too deep\n");
			Sleep(5000);
			return;
		}
	}
		
	printf("Working Directory: %s\n  ", szCmdPmtPath);
	printf("Input File:        %s\n", szCmdPmtInputTitleName);

	fopen_s(&fd, szCmdPmtInputFileName, "r");
	if(fd == NULL)
	{
		printf("Unable to open file %s\n\n", szCmdPmtInputFileName);
		return;
	}

	// Scan the file.
	lineNumber = 0;
	while(NULL != fgets(szLine, SIZE_256, fd))
	{

		// Reset to the current file directory.
		SetCurrentDirectory(szCmdPmtPath);

		// Initialize/update variables.
		lineNumber++;

		// Skip comments and irrelevant tokens in the text file describing the test cases.
		if(szLine[0] == '%' || szLine[0] == ' ' || strlen(szLine) <= 1)
			continue;

		totalCount++;
		// A scenario will have, at a minimum, 5 characters (the name plus ".sce").
		if(strlen(szLine) < 5)
		{
			printf("\"%s\" on line %d is an invalid token, skipping...\n", szLine, lineNumber);
			skippedCount++;
			continue;
		}

		// Read in the name of the scenario to run and optional switches.
		memset(szSwitch, 0, NUMVALIDSWITCHES*SIZE_16);
		numLineConverstions = sscanf_s(szLine, "%s %s %s", szScenarioFileName, szSwitch[0], szSwitch[1], szSwitch[2]);
		if(numLineConverstions > NUMVALIDSWITCHES+1)
		{
			printf("\"%s\" on line %d has too many tokens, skipping...\n", szLine, lineNumber);
			skippedCount++;
			continue;
		}

		if(szLine[strlen(szLine) - 1] == '\n')
			szLine[strlen(szLine) - 1] = 0;
		printf("\n%s            \n", szLine);

		// Verify the extension is correct.
		staticLib.GetExtension(szScenarioFileName, szBuffer, SIZE_256);
		if(strcmp(szBuffer, ".sce") != 0)
		{
			printf("\"%s\" on line %d has invalid extension, skipping...\n", szScenarioFileName, lineNumber);
			skippedCount++;
			continue;
		}

		// Default values
		aeDb = 0.25f;
		aeCycleOn = FALSE;
		generateNew = FALSE;
		aeOn = FALSE;

		// Determine switches (magic number 3 because at this time there can be only 
		// three switches).
		for(i=0; i<NUMVALIDSWITCHES && strlen(szSwitch[i]); i++)
		{
			if(strcmp(szSwitch[i], "-g") == 0)
				generateNew = TRUE;
			else if(strcmp(szSwitch[i], "-a") == 0)
				aeOn = TRUE;
			else if(strcmp(szSwitch[i], "-d") == 0)
			{
				generateNew = TRUE;
				deleteOuputFile = TRUE;
			}
			else
			{
				printf("\"%s\" on line %d has an invalid switch, skipping...\n", szLine, lineNumber);
				skippedCount++;
			}
		}
		RunScenario(szScenarioFileName, generateNew, aeOn, deleteOuputFile, .001, lineNumber);
	}
	fclose(fd);

	printf("\n");

	printf("Summary Results:\n");
	printf("Total Files:%d  Total Errors:%d\n", totalCount, errorCount);
	printf("\tGenerate New: %d\n", generateNewCount);
	printf("\tComparisons: Success:%d  Fail:%d  Skipped:%d\n", successCount, failCount, skippedCount);
}