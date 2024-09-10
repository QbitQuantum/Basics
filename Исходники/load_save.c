	void setupUserHomeDirectory()
	{
		STRNCPY(gameSavePath, "", sizeof(gameSavePath));
		STRNCPY(tempFile, "tmpsave", sizeof(tempFile));
		STRNCPY(saveFileIndex, "saveheader", sizeof(saveFileIndex));
		STRNCPY(continueFile, "continuesave", sizeof(continueFile));
	}