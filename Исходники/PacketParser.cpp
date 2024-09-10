bool checkArgs(int argc, char* argv[], char** inFile, outFormat &out, int &rowStart, int &rowEnd)
{
	char env[256];
	if (argc < 2)
	{
		std::string tmpFile;
		//printf("No input file specified\n");
//#ifdef _DEBUG
#if 1
		*inFile = _strdup("c:\\Users\\David\\Documents\\packets.txt");
		if (GetEnvironmentVariableA("QUERY_STRING", env, 256))
		{
			//printf("<query>%s</query>\n", env);
			parseQueryString(env, rowStart, rowEnd);
		}
		out = XML;
#else
		std::cout << "Filename: ";
		std::getline(std::cin, tmpFile);
		*inFile = _strdup(tmpFile.c_str());
#endif
#ifdef _DEBUG
		printf("inFile is %s\n", *inFile);
#endif
		return true;
		//return false;	//needs an input file
	}
	if (argc>2)
	{
		*inFile = _strdup(argv[1]);

		for (int i = 2; i <= argc; i++)
		{
			if (strcmp(argv[i], "-x") == 0)
			{
				if (out == CSV)
				{
					printf("-x cannot be specified along with -c\n");
					return false;
				}
				else
					out = XML;
				continue;
			}
			if (strcmp(argv[i], "-c") == 0)
			{
				if (out == XML)
				{
					printf("-c cannot be specified along with -x\n");
					return false;
				}
				else
					out = CSV;
				continue;
			}
			if (strncmp(argv[i], "-r", 2) == 0)
			{
				//TODO parse beginning and ending rows
				continue;
			}
			return false;
		}
	}
	return true;
}