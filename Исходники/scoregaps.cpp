SCORE ScoreGaps(const MSA &msa, const unsigned DiffCols[], unsigned DiffColCount)
	{
    MuscleContext *ctx = getMuscleContext();
    unsigned &g_ColCount = ctx->scoregaps.g_ColCount;
    unsigned &g_MaxSeqCount = ctx->scoregaps.g_MaxSeqCount;
    unsigned &g_MaxColCount = ctx->scoregaps.g_MaxColCount;
    GAPINFO** &g_Gaps = ctx->scoregaps.g_Gaps;
    bool* &g_ColDiff = ctx->scoregaps.g_ColDiff;
    
#if	TRACE
	{
	Log("ScoreGaps\n");
	Log("DiffCols ");
	for (unsigned i = 0; i < DiffColCount; ++i)
		Log(" %u", DiffCols[i]);
	Log("\n");
	Log("msa=\n");
	msa.LogMe();
	Log("\n");
	}
#endif
	const unsigned SeqCount = msa.GetSeqCount();
	const unsigned ColCount = msa.GetColCount();
	g_ColCount = ColCount;

	if (SeqCount > g_MaxSeqCount)
		{
		delete[] g_Gaps;
		g_MaxSeqCount = SeqCount + 256;
		g_Gaps = new GAPINFO *[g_MaxSeqCount];
		}
	memset(g_Gaps, 0, SeqCount*sizeof(GAPINFO *));

	if (ColCount > g_MaxColCount)
		{
		delete[] g_ColDiff;
		g_MaxColCount = ColCount + 256;
		g_ColDiff = new bool[g_MaxColCount];
		}

	memset(g_ColDiff, 0, g_ColCount*sizeof(bool));
	for (unsigned i = 0; i < DiffColCount; ++i)
		{
		unsigned Col = DiffCols[i];
		assert(Col < ColCount);
		g_ColDiff[Col] = true;
		}

	for (unsigned SeqIndex = 0; SeqIndex < SeqCount; ++SeqIndex)
		FindIntersectingGaps(msa, SeqIndex);

#if	TRACE
	{
	Log("\n");
	Log("Intersecting gaps:\n");
	Log("      ");
	for (unsigned Col = 0; Col < ColCount; ++Col)
		Log("%c", g_ColDiff[Col] ? '*' : ' ');
	Log("\n");
	Log("      ");
	for (unsigned Col = 0; Col < ColCount; ++Col)
		Log("%d", Col%10);
	Log("\n");
	for (unsigned Seq = 0; Seq < SeqCount; ++Seq)
		{
		Log("%3d:  ", Seq);
		for (unsigned Col = 0; Col < ColCount; ++Col)
			Log("%c", msa.GetChar(Seq, Col));
		Log("  :: ");
		for (GAPINFO *GI = g_Gaps[Seq]; GI; GI = GI->Next)
			Log(" (%d,%d)", GI->Start, GI->End);
		Log("  >%s\n", msa.GetSeqName(Seq));
		}
	Log("\n");
	}
#endif

	SCORE Score = 0;
	for (unsigned Seq1 = 0; Seq1 < SeqCount; ++Seq1)
		{
		const WEIGHT w1 = msa.GetSeqWeight(Seq1);
		for (unsigned Seq2 = Seq1 + 1; Seq2 < SeqCount; ++Seq2)
			{
			const WEIGHT w2 = msa.GetSeqWeight(Seq2);
//			const SCORE Pair = ScorePair(Seq1, Seq2);
			const SCORE Pair = ScoreSeqPairGaps(msa, Seq1, msa, Seq2);
			Score += w1*w2*Pair;
#if	TRACE
			Log("Seq1=%u Seq2=%u ScorePair=%.4g w1=%.4g w2=%.4g Sum=%.4g\n",
			  Seq1, Seq2, Pair, w1, w2, Score);
#endif
			}
		}

	return Score;
	}