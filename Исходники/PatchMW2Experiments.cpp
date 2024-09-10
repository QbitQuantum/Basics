void DumpRawFiles()
{
	if (Cmd_Argc() != 2)
	{
		return;
	}

	rawFileNames[0] = Cmd_Argv(1);
	currentRawFile = 1;

	for (int i = 0; i < currentRawFile; i++)
	{
		const char* name = rawFileNames[i];
		memset(rawFileBuffer, 0, RAWFILE_BUFSIZE);

		if (LoadRawFile(name, rawFileBuffer, RAWFILE_BUFSIZE))
		{
			char filename[512];
			char dir[512];
			size_t length = strlen(rawFileBuffer);
			sprintf(filename, "%s/%s", "maw", name);

			GetCurrentDirectoryA(sizeof(dir), dir);
			strcat(dir, "/");
			strcat(dir, filename);
			*(strrchr(dir, '/')) = '\0';

			size_t strl = strlen(dir);

			for (size_t i = 0; i < strl; i++)
			{
				if (dir[i] == '/') dir[i] = '\\';
			}

			SHCreateDirectoryExA(NULL, dir, NULL);

			FILE* file = fopen(filename, "wb");

			if (file)
			{
				fwrite(rawFileBuffer, 1, length, file);
				fclose(file);
			}
		}
	}

	currentRawFile = 0;

	return;

	for (int i = 0; i < currentSTable; i++)
	{
		const char* name = sTableNames[i];
		stringTable_t* stringTable;

		if (stringTable = (stringTable_t*)DB_FindXAssetHeader(37, name))
		{
			char filename[512];
			char dir[512];
			sprintf(filename, "%s/%s", "raw", name);

			GetCurrentDirectoryA(sizeof(dir), dir);
			strcat(dir, "/");
			strcat(dir, filename);
			*(strrchr(dir, '/')) = '\0';

			size_t strl = strlen(dir);

			for (size_t i = 0; i < strl; i++)
			{
				if (dir[i] == '/') dir[i] = '\\';
			}

			SHCreateDirectoryExA(NULL, dir, NULL);

			FILE* file = fopen(filename, "w");

			if (file)
			{
				int currentColumn = 0;
				int currentRow = 0;
				int total = stringTable->columns * stringTable->rows;

				for (int i = 0; i < total; i++) {
					char* current = stringTable->data[i * 2];

					fprintf(file, "%s", current);

					bool isNext = ((i + 1) % stringTable->columns) == 0;

					if (isNext) {
						fprintf(file, "\n");
					} else {
						fprintf(file, ",");
					}

					fflush(file);
				}

				fclose(file);
			}
		}
	}

	currentSTable = 0;
}