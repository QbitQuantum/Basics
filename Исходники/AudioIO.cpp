const CHR *AudioIO::detectSourceType(const CHR *const fileName, const bool verbose)
{
	if (verbose)
	{
		PRINT_NFO(TXT("------- Audio I/O -------"));
	}
	
	uint8_t type = AUDIO_LIB_NULL;
	const bool bStdIn = (STRCASECMP(fileName, TXT("-")) == 0);

	if (bStdIn || PATH_ISREG(fileName))
	{
		if (FILE *const file = bStdIn ? stdin : FOPEN(fileName, TXT("rb")))
		{
			if (FD_ISREG(FILENO(file)))
			{
				for (size_t i = 0; g_audioIO_mapping[i].id; ++i)
				{
					if (verbose)
					{
						PRINT2_NFO(TXT("Trying input module ") FMT_CHR TXT("..."), g_audioIO_mapping[i].name);
					}
					if (checkFileType(g_audioIO_mapping[i].checkFileType, file))
					{
						type = g_audioIO_mapping[i].id;
						if (verbose)
						{
							PRINT_NFO(TXT("succeeded."));
						}
						break;
					}
				}
			}
			if (!bStdIn)
			{
				fclose(file);
			}
		}
	}

	if (verbose)
	{
		if(type == AUDIO_LIB_NULL)
		{
			PRINT_NFO(TXT("No suitable input module found -> falling back to default!"));
		}
		PRINT_NFO(TXT("------- Audio I/O -------\n"));
	}

	return getLibName(type);
}