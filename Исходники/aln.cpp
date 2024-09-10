void MSA::ToAlnFile(TextFile &File) const
	{
	if (getMuscleContext()->params.g_bClwStrict)
		File.PutString("CLUSTAL W (1.81) multiple sequence alignment\n");
	else
		{
		File.PutString("MUSCLE ("
		  MUSCLE_MAJOR_VERSION "." MUSCLE_MINOR_VERSION ")"
		  " multiple sequence alignment\n");
		File.PutString("\n");
		}

	int iLongestNameLength = 0;
	for (unsigned uSeqIndex = 0; uSeqIndex < GetSeqCount(); ++uSeqIndex)
		{
		const char *ptrName = GetSeqName(uSeqIndex);
		const char *ptrBlank = strchr(ptrName, ' ');
		int iLength;
		if (0 != ptrBlank)
			iLength = (int) (ptrBlank - ptrName);
		else
			iLength = (int) strlen(ptrName);
		if (iLength > iLongestNameLength)
			iLongestNameLength = iLength;
		}
	if (iLongestNameLength > MAX_NAME)
		iLongestNameLength = MAX_NAME;
	if (iLongestNameLength < MIN_NAME)
		iLongestNameLength = MIN_NAME;

	unsigned uLineCount = (GetColCount() - 1)/uCharsPerLine + 1;
	for (unsigned uLineIndex = 0; uLineIndex < uLineCount; ++uLineIndex)
		{
		File.PutString("\n");
		unsigned uStartColIndex = uLineIndex*uCharsPerLine;
		unsigned uEndColIndex = uStartColIndex + uCharsPerLine - 1;
		if (uEndColIndex >= GetColCount())
			uEndColIndex = GetColCount() - 1;
		char Name[MAX_NAME+1];
		for (unsigned uSeqIndex = 0; uSeqIndex < GetSeqCount(); ++uSeqIndex)
			{
			const char *ptrName = GetSeqName(uSeqIndex);
			const char *ptrBlank = strchr(ptrName, ' ');
			int iLength;
			if (0 != ptrBlank)
				iLength = (int) (ptrBlank - ptrName);
			else
				iLength = (int) strlen(ptrName);
			if (iLength > MAX_NAME)
				iLength = MAX_NAME;
			memset(Name, ' ', MAX_NAME);
			memcpy(Name, ptrName, iLength);
			Name[iLongestNameLength] = 0;

			File.PutFormat("%s      ", Name);
			for (unsigned uColIndex = uStartColIndex; uColIndex <= uEndColIndex;
			  ++uColIndex)
				{
				const char c = GetChar(uSeqIndex, uColIndex);
				File.PutFormat("%c", toupper(c));
				}
			File.PutString("\n");
			}

		memset(Name, ' ', MAX_NAME);
		Name[iLongestNameLength] = 0;
		File.PutFormat("%s      ", Name);
		for (unsigned uColIndex = uStartColIndex; uColIndex <= uEndColIndex;
		  ++uColIndex)
			{
			const char c = GetAlnConsensusChar(*this, uColIndex);
			File.PutChar(c);
			}
		File.PutString("\n");
		}
	}