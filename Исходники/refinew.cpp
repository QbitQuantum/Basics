void RefineW(const MSA &msaIn, MSA &msaOut)
	{
	const unsigned uSeqCount = msaIn.GetSeqCount();
	const unsigned uColCount = msaIn.GetColCount();

// Reserve same nr seqs, 20% more cols
	const unsigned uReserveColCount = (uColCount*120)/100;
	msaOut.SetSize(uSeqCount, uReserveColCount);

	for (unsigned uSeqIndex = 0; uSeqIndex < uSeqCount; ++uSeqIndex)
		{
		msaOut.SetSeqName(uSeqIndex, msaIn.GetSeqName(uSeqIndex));
		msaOut.SetSeqId(uSeqIndex, msaIn.GetSeqId(uSeqIndex));
		}

	const unsigned uWindowCount = (uColCount + g_uRefineWindow.get() - 1)/g_uRefineWindow.get();
	if (0 == g_uWindowTo.get())
		g_uWindowTo.get() = uWindowCount - 1;

#if	MEMDEBUG
	_CrtSetBreakAlloc(1560);
#endif

	if (g_uWindowOffset.get() > 0)
		{
		MSA msaTmp;
		MSAFromColRange(msaIn, 0, g_uWindowOffset.get(), msaOut);
		}

	if (!g_bQuiet.get())
		fprintf(stderr, "\n");
	for (unsigned uWindowIndex = g_uWindowFrom.get(); uWindowIndex <= g_uWindowTo.get(); ++uWindowIndex)
		{
		if (!g_bQuiet.get())
			fprintf(stderr, "Window %d of %d    \r", uWindowIndex, uWindowCount);
		const unsigned uColFrom = g_uWindowOffset.get() + uWindowIndex*g_uRefineWindow.get();
		unsigned uColTo = uColFrom + g_uRefineWindow.get() - 1;
		if (uColTo >= uColCount)
			uColTo = uColCount - 1;
		assert(uColTo >= uColFrom);

		SeqVect v;
		SeqVectFromMSACols(msaIn, uColFrom, uColTo, v);

#if	MEMDEBUG
		_CrtMemState s1;
		_CrtMemCheckpoint(&s1);
#endif
		// Begin AED 5/20/06
		// remove any empty seqs in this window
		std::vector< size_t > empty_seqs;
		SeqVect vr;
		for( size_t seqI = 0; seqI < v.size(); ++seqI )
		{
			if( v[seqI]->size() == 0 )
				empty_seqs.push_back(seqI);
			else
				vr.push_back(v[seqI]);
		}
		std::vector< unsigned > seqid_map( vr.size() );
		for( size_t seqI = 0; seqI < vr.size(); ++seqI )
		{
			seqid_map[seqI] = vr[seqI]->GetId();
			vr[seqI]->SetId(seqI);
		}

		MSA msaTmp;
		if( vr.size() > 1 )
			MUSCLE(vr, msaTmp);

		// remap the seqids to their original state
		for( size_t seqI = 0; seqI < vr.size(); ++seqI )
			vr[seqI]->SetId(seqid_map[seqI]);

		// merge empty seqs back in
		{
			const unsigned uSeqCount = msaOut.GetSeqCount();

			const unsigned uColCount1 = msaOut.GetColCount();
			const unsigned uColCount2 = vr.size() > 1 ? msaTmp.GetColCount() : vr[0]->size();
			const unsigned uColCountCat = uColCount1 + uColCount2;
			for( unsigned seqI = 0; seqI < vr.size(); ++seqI )
			{
				unsigned uSeqIndex = msaOut.GetSeqIndex(seqid_map[seqI]);
				if( vr.size() > 1 )
				{
					unsigned uSeqIndex2 = msaTmp.GetSeqIndex(seqI);
					for (unsigned uColIndex = 0; uColIndex < uColCount2; ++uColIndex)
					{
						const char c = msaTmp.GetChar(uSeqIndex2, uColIndex);
						msaOut.SetChar(uSeqIndex, uColCount1 + uColIndex, c);
					}
				}else{
					for (unsigned uColIndex = 0; uColIndex < uColCount2; ++uColIndex)
					{
						const char c = vr[0]->GetChar(uColIndex);
						msaOut.SetChar(uSeqIndex, uColCount1 + uColIndex, c);
					}
				}
			}
			for( unsigned seqI = 0; seqI < empty_seqs.size(); ++seqI )
			{
				unsigned uSeqId2 = v[empty_seqs[seqI]]->GetId();
				unsigned uSeqIndex = msaOut.GetSeqIndex(uSeqId2);
				for (unsigned uColIndex = 0; uColIndex < uColCount2; ++uColIndex)
				{
					msaOut.SetChar(uSeqIndex, uColCount1 + uColIndex, '-');
				}
			}
			vr.clear();
		}
//		AppendMSA(msaOut, msaTmp);
		// end AED 5/20/06

		if (uWindowIndex == g_uSaveWindow.get())
			{
			MSA msaInTmp;
			unsigned uOutCols = msaOut.GetColCount();
			unsigned un = uColTo - uColFrom + 1;
			MSAFromColRange(msaIn, uColFrom, un, msaInTmp);

			char fn[256];
			sprintf(fn, "win%d_inaln.tmp", uWindowIndex);
			TextFile fIn(fn, true);
			msaInTmp.ToFile(fIn);

			sprintf(fn, "win%d_inseqs.tmp", uWindowIndex);
			TextFile fv(fn, true);
			v.ToFile(fv);

			sprintf(fn, "win%d_outaln.tmp", uWindowIndex);
			TextFile fOut(fn, true);
			msaTmp.ToFile(fOut);
			}

#if	MEMDEBUG
		void FreeDPMemSPN();
		FreeDPMemSPN();

		_CrtMemState s2;
		_CrtMemCheckpoint(&s2);

		_CrtMemState s;
		_CrtMemDifference(&s, &s1, &s2);

		_CrtMemDumpStatistics(&s);
		_CrtMemDumpAllObjectsSince(&s1);
		exit(1);
#endif
//#if	DEBUG
//		AssertMSAEqIgnoreCaseAndGaps(msaInTmp, msaTmp);
//#endif
		}
	if (!g_bQuiet.get())
		fprintf(stderr, "\n");

//	AssertMSAEqIgnoreCaseAndGaps(msaIn, msaOut);//@@uncomment!
	}