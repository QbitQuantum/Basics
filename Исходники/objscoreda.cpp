static SCORE ScoreSeqPair(const MSA &msa1, unsigned uSeqIndex1,
  const MSA &msa2, unsigned uSeqIndex2, SCORE *ptrLetters, SCORE *ptrGaps)
	{
	g_ptrMSA1.get() = &msa1;
	g_ptrMSA2.get() = &msa2;
	g_uSeqIndex1.get() = uSeqIndex1;
	g_uSeqIndex2.get() = uSeqIndex2;

	const unsigned uColCount = msa1.GetColCount();
	const unsigned uColCount2 = msa2.GetColCount();
	if (uColCount != uColCount2)
		Quit("ScoreSeqPair, different lengths");

#if	TRACE
	Log("ScoreSeqPair\n");
	Log("%16.16s  ", msa1.GetSeqName(uSeqIndex1));
	for (unsigned i = 0; i < uColCount; ++i)
		Log("%c", msa1.GetChar(uSeqIndex1, i));
	Log("\n");
	Log("%16.16s  ", msa2.GetSeqName(uSeqIndex2));
	for (unsigned i = 0; i < uColCount; ++i)
		Log("%c", msa1.GetChar(uSeqIndex2, i));
	Log("\n");
#endif

	SCORE scoreTotal = 0;

// Substitution scores
	unsigned uFirstLetter1 = uInsane;
	unsigned uFirstLetter2 = uInsane;
	unsigned uLastLetter1 = uInsane;
	unsigned uLastLetter2 = uInsane;
	for (unsigned uColIndex = 0; uColIndex < uColCount; ++uColIndex)
		{
		bool bGap1 = msa1.IsGap(uSeqIndex1, uColIndex);
		bool bGap2 = msa2.IsGap(uSeqIndex2, uColIndex);
		bool bWildcard1 = msa1.IsWildcard(uSeqIndex1, uColIndex);
		bool bWildcard2 = msa2.IsWildcard(uSeqIndex2, uColIndex);

		if (!bGap1)
			{
			if (uInsane == uFirstLetter1)
				uFirstLetter1 = uColIndex;
			uLastLetter1 = uColIndex;
			}
		if (!bGap2)
			{
			if (uInsane == uFirstLetter2)
				uFirstLetter2 = uColIndex;
			uLastLetter2 = uColIndex;
			}

		if (bGap1 || bGap2 || bWildcard1 || bWildcard2)
			continue;

		unsigned uLetter1 = msa1.GetLetter(uSeqIndex1, uColIndex);
		unsigned uLetter2 = msa2.GetLetter(uSeqIndex2, uColIndex);

		SCORE scoreMatch = (*g_ptrScoreMatrix.get())[uLetter1][uLetter2];
		scoreTotal += scoreMatch;
#if	TRACE
		Log("%c <-> %c = %7.1f  %10.1f\n",
		  msa1.GetChar(uSeqIndex1, uColIndex),
		  msa2.GetChar(uSeqIndex2, uColIndex),
		  scoreMatch,
		  scoreTotal);
#endif
		}
	
	*ptrLetters = scoreTotal;

// Gap penalties
	unsigned uGapLength = uInsane;
	unsigned uGapStartCol = uInsane;
	bool bGapping1 = false;
	bool bGapping2 = false;

	for (unsigned uColIndex = 0; uColIndex < uColCount; ++uColIndex)
		{
		bool bGap1 = msa1.IsGap(uSeqIndex1, uColIndex);
		bool bGap2 = msa2.IsGap(uSeqIndex2, uColIndex);

		if (bGap1 && bGap2)
			continue;

		if (bGapping1)
			{
			if (bGap1)
				++uGapLength;
			else
				{
				bGapping1 = false;
				bool bNTerm = (uFirstLetter2 == uGapStartCol);
				bool bCTerm = (uLastLetter2 + 1 == uColIndex);
				SCORE scoreGap = GapPenalty(uGapLength, bNTerm || bCTerm);
				scoreTotal += scoreGap;
#if	TRACE
				LogGap(uGapStartCol, uColIndex - 1, uGapLength, bNTerm, bCTerm);
				Log("GAP         %7.1f  %10.1f\n",
				  scoreGap,
				  scoreTotal);
#endif
				}
			continue;
			}
		else
			{
			if (bGap1)
				{
				uGapStartCol = uColIndex;
				bGapping1 = true;
				uGapLength = 1;
				continue;
				}
			}

		if (bGapping2)
			{
			if (bGap2)
				++uGapLength;
			else
				{
				bGapping2 = false;
				bool bNTerm = (uFirstLetter1 == uGapStartCol);
				bool bCTerm = (uLastLetter1 + 1 == uColIndex);
				SCORE scoreGap = GapPenalty(uGapLength, bNTerm || bCTerm);
				scoreTotal += scoreGap;
#if	TRACE
				LogGap(uGapStartCol, uColIndex - 1, uGapLength, bNTerm, bCTerm);
				Log("GAP         %7.1f  %10.1f\n",
				  scoreGap,
				  scoreTotal);
#endif
				}
			}
		else
			{
			if (bGap2)
				{
				uGapStartCol = uColIndex;
				bGapping2 = true;
				uGapLength = 1;
				}
			}
		}

	if (bGapping1 || bGapping2)
		{
		SCORE scoreGap = GapPenalty(uGapLength, true);
		scoreTotal += scoreGap;
#if	TRACE
		LogGap(uGapStartCol, uColCount - 1, uGapLength, false, true);
		Log("GAP         %7.1f  %10.1f\n",
		  scoreGap,
		  scoreTotal);
#endif
		}
	*ptrGaps = scoreTotal - *ptrLetters;
	return scoreTotal;
	}