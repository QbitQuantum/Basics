void MSA::ToFASTAFile(TextFile &File) const
	{
	const unsigned uColCount = GetColCount();
	assert(uColCount > 0);
	const unsigned uLinesPerSeq = (GetColCount() - 1)/FASTA_BLOCK + 1;
	const unsigned uSeqCount = GetSeqCount();

	for (unsigned uSeqIndex = 0; uSeqIndex < uSeqCount; ++uSeqIndex)
		{
		File.PutString(">");
		File.PutString(GetSeqName(uSeqIndex));
		File.PutString("\n");

		unsigned n = 0;
		for (unsigned uLine = 0; uLine < uLinesPerSeq; ++uLine)
			{
			unsigned uLetters = uColCount - uLine*FASTA_BLOCK;
			if (uLetters > FASTA_BLOCK)
				uLetters = FASTA_BLOCK;
			for (unsigned i = 0; i < uLetters; ++i)
				{
				char c = GetChar(uSeqIndex, n);
				File.PutChar(c);
				++n;
				}
			File.PutChar('\n');
			}
		}
	}