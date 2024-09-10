/*----------------------------------------------------------------------------------------------
	The standard method for generating a segment in a paragraph, where a line break might be
	necessary.

	Generally called with fEndLine true; then change segment to make it false if we want to
	try to put something else after.

	TODO SharonC?: try implementing and see whether we can handle all the possible complications relating
	to adjacent segments that can't be separated, such as English parens around Hebrew text.

	@param pgjus		- NULL if no justification will ever be needed for the resulting segment
	@param ichMin/Lim			- part of string to use
	@param ichwLimBacktrack		- when backtracking, where to start looking for a new break
	@param fNeedFinalBreak		- if false, assume it is okay to make a segment ending at
									ichwLim; if true, assume the text source has at least one
									more character at ichwLim, and end the segment at ichwLim
									only if that is a valid break point
	@param fStartLine			- seg is logically first on line? (we assume it is logically last)
	@param dxMaxWidth			- available width in x coords of graphics object
	@param lbPref				- try for longest segment ending with this breakweight
	@param lbMax				- max (last resort) breakweight if no preferred break possible
	@param twsh					- how we are handling trailing white-space
	@param fParaRtl				- overall paragraph direction
	@param pplsegRet			- segment produced, or null if nothing fits
	@param pichwLimSeg			- end of segment produced, beginning of next
	@param pdxWidth				- width of newly-created segment
	@param pest					- what caused the segment to end
	@param cpPrev				- byte size of pbPrevSegDat buffer
	@param pbPrevSegDat			- for initializing from previous segment
	@param cbNextMax			- max size of pbNextSegDat buffer
	@param pbNextSegDat			- for initializing next segment
	@param pcbNextSegDat		- size of pbNextSegDat buffer
	@param pdichwContext		- for the following segment, the index of the first char of
									interest to it; ie, edits before this character will not
									affect how the next segment behaves
----------------------------------------------------------------------------------------------*/
STDMETHODIMP FwGrEngine::FindBreakPoint(
	IVwGraphics * pvg, IVwTextSource * pts, IVwJustifier * pvjus,
	int ichwMin, int ichwLim, int ichwLimBacktrack,
	ComBool fNeedFinalBreak,
	ComBool fStartLine,
	int dxMaxWidth,
	LgLineBreak lbPref, LgLineBreak lbMax,
	LgTrailingWsHandling twsh, ComBool fParaRtl,
	ILgSegment ** ppsegRet,
	int * pdichwLimSeg,
	int * pdxWidth, LgEndSegmentType * pest,
	ILgSegment * plgsegPrev)
{
	BEGIN_COM_METHOD;
	ChkComArgPtr(pvg);
	ChkComArgPtr(pts);
	ChkComArgPtrN(pvjus);
	ChkComOutPtr(ppsegRet);
	ChkComOutPtr(pdichwLimSeg);
	ChkComArgPtr(pdxWidth);
	ChkComArgPtr(pest);

	HRESULT hr = S_OK;

	// Use wrappers that fit what is expected by the Graphite implementation code:
	//////FwGrGraphics gg(pvg);

	// Create these on the heap so they can be stored in the segment.
	FwGrTxtSrc * pgts = new FwGrTxtSrc(pts, m_useNFC);
	//FwGrJustifier * pgjus = (pvjus) ? new FwGrJustifier(pvjus) : NULL;
	if (pvjus && !s_pgjus)
	{
		s_pgjus = new FwGrJustifier(pvjus);
		m_pgjus = s_pgjus; // make this engine responsible for deleting it
	}

	FwGrSegmentPtr qfwgrseg;
	if (*ppsegRet)
	{
		return E_INVALIDARG;
		//CheckHr((*ppsegRet)->QueryInterface(CLSID_FwGrSegment, (void**)&qfwgrseg));
		//pgrseg = qfwgrseg->GraphiteSegment();
	}

	Segment * psegPrev = NULL;
	if (plgsegPrev)
	{
		FwGrSegment * pfwgrseg = dynamic_cast<FwGrSegment *>(plgsegPrev);
		if (pfwgrseg)
			psegPrev = pfwgrseg->GraphiteSegment();
		// otherwise, not a Graphite segment
	}

	// Need-final-break is true if and only if we are backtracking.
	Assert((ichwLim != ichwLimBacktrack) == fNeedFinalBreak);

	// Adjust the font in the graphics device for super/subscripting.

	SetUpGraphics(pvg, pgts, ichwMin);

	HDC hdc;
	IVwGraphicsWin32Ptr qvg32;
	CheckHr(pvg->QueryInterface(IID_IVwGraphicsWin32, (void **)&qvg32));
	CheckHr(qvg32->GetDeviceContext(&hdc));
	////gg.GetDeviceContext(&hdc);

	Segment * pgrseg;
	WinFont * pfontSeg;
	try
	{
		// DON'T use m_pfont, which might be for the wrong size; use a new font
		// specifically for this size font.
		FwWinFont font(hdc);
		int xInch, yInch;
		pvg->get_XUnitsPerInch(&xInch);
		pvg->get_YUnitsPerInch(&yInch);
		font.SetDPI(xInch, yInch);

		std::ofstream strmLog;
		std::ostream * pstrmLog = CreateLogFile(strmLog, (psegPrev != NULL));

		// for testing UTF-8:
		//gr::utf16 prgchw[1000];
		//int cchwLen;
		//pts->get_Length(&cchwLen);
		//pts->Fetch(ichwMin, cchwLen, prgchw);
		//ichwLim = CountUtf8FromUtf16(prgchw, ichwLim);
		//ichwLimBacktrack = ichwLim;
		/////////////////////

		LayoutEnvironment layout;
		layout.setStartOfLine(fStartLine);
		layout.setEndOfLine(true);
		layout.setBestBreak(lbPref);
		layout.setWorstBreak(lbMax);
		layout.setRightToLeft(fParaRtl);
		layout.setTrailingWs(twsh);
		layout.setPrevSegment(psegPrev);
		layout.setJustifier(s_pgjus);
		layout.setLoggingStream(pstrmLog);
		layout.setDumbFallback(true);

		//for allowing hyphen breaks:
		//layout.setBestBreak(max(klbHyphenBreak, lbPref));
		//layout.setWorstBreak(max(klbHyphenBreak, lbMax));

		bool fBacktracking = (ichwLimBacktrack < ichwLim);
		int grIchwMin = pgts->VwToGrOffset(ichwMin);
		int grIchwLim = fBacktracking ? pgts->VwToGrOffset(ichwLimBacktrack) : pgts->VwToGrOffset(ichwLim);

		pgrseg = new LineFillSegment(&font, pgts, &layout,
			grIchwMin, grIchwLim,
			(float)dxMaxWidth, fBacktracking);
		gr::Font & fontSeg = pgrseg->getFont();
		pfontSeg = dynamic_cast<WinFont *>(&fontSeg);
		pfontSeg->replaceDC(hdc);
		*pest = pgrseg->segmentTermination();
		if (*pest != kestNothingFit)
		{
			int grIchwLimSeg = pgrseg->stopCharacter() - pgrseg->startCharacter();
			*pdichwLimSeg = pgts->GrToVwOffset(grIchwLimSeg);
			*pdxWidth = gr::GrEngine::RoundFloat(pgrseg->advanceWidth());
			// there is a limit in the number of pixels (about 2^16) that the ExtTextOut function
			// can render, which is what Graphite uses to render text on Windows. If this
			// segment is over that limit, we reduce the number of characters in this segment
			// so that when it is rendered it is less than the limit. The main place this
			// can happen is in concordance views.
			// TODO (DamienD): This fix removes characters from the end of the segment. If the
			// segment is too long on the left side of the arrow in the concordance view,
			// characters should be removed from the beginning. This case would have to be
			// handled in Views somewhere.
			// TODO (DamienD): If Graphite ever fixes the limit, we can safely remove this
			// hack.
			if (*pdxWidth > SHRT_MAX)
			{
				delete pgrseg;
				int avgCharWidth = *pdxWidth / (grIchwMin + grIchwLimSeg);
				// we use 30000 here, because avgCharWidth is just an estimate,
				// this gives us some padding to ensure that the resulting segment
				// is less than the limit
				grIchwLim = grIchwMin + (30000 / avgCharWidth);
				pgrseg = new LineFillSegment(&font, pgts, &layout,
					grIchwMin, grIchwLim,
					(float)dxMaxWidth, fBacktracking);

				// reset variables for new segment
				gr::Font & fontSeg = pgrseg->getFont();
				pfontSeg = dynamic_cast<WinFont *>(&fontSeg);
				pfontSeg->replaceDC(hdc);

				*pest = pgrseg->segmentTermination();
				if (*pest != kestNothingFit)
				{
					*pdichwLimSeg = pgts->GrToVwOffset(pgrseg->stopCharacter() - pgrseg->startCharacter());
					*pdxWidth = gr::GrEngine::RoundFloat(pgrseg->advanceWidth());
				}
			}
		}

		strmLog.close();
	}
	catch (FontException & fexptn)
	{
		// Error in initializing the font.
		FontErrorCode ferr = fexptn.errorCode;
		LgCharRenderProps chrp;
		int ichwMinBogus, ichwLimBogus;
		pgts->GetCharProps(ichwMin, &chrp, &ichwMinBogus, &ichwLimBogus);
		StrUni stuMsg = L"Error in initializing Graphite font ";
		stuMsg.Append(chrp.szFaceName);
		stuMsg.Append(": ");
		std::wstring stuErrMsg = FontLoadErrorDescription(ferr, 0, 0, &hr);
		stuMsg.Append(stuErrMsg.c_str());
		StackDumper::RecordError(IID_IRenderEngine, stuMsg, L"SIL.Graphite.FwGrEngine", 0, L"");
		return hr;
	}

	// if we are at the end of the requested range, but the text source still has more text in
	// it, Graphite will determine that the break was bad or okay, even though it broke
	// because there was no more text, so we go ahead and change the reason here to no more text
	if (ichwMin + *pdichwLimSeg == ichwLim && (*pest == kestOkayBreak || *pest == kestBadBreak))
		*pest = kestNoMore;

	bool fError = false;
	std::pair<GlyphIterator, GlyphIterator> pairGfit = pgrseg->glyphs();
	GlyphIterator gfit = pairGfit.first;
	GlyphIterator gfitEnd = pairGfit.second;
	for ( ; gfit != gfitEnd ; ++gfit)
	{
		if ((*gfit).erroneous())
		{
			fError = true;
			break;
		}
	}

	if (fError)
	{
		LgCharRenderProps chrp;
		int ichwMinBogus, ichwLimBogus;
		pgts->GetCharProps(ichwMin, &chrp, &ichwMinBogus, &ichwLimBogus);
		StrUni stuMsg = L"Error in Graphite rendering using font ";
		stuMsg.Append(chrp.szFaceName);
		StackDumper::RecordError(IID_IRenderEngine, stuMsg, L"SIL.Graphite.FwGrEngine", 0, L"");
		hr = E_FAIL;
	}

	//// TEMPORARY - for testing
	//pairGfit = pgrseg->glyphs();
	//gfit = pairGfit.first;
	//gfitEnd = pairGfit.second;
	//for ( ; gfit != gfitEnd ; ++gfit)
	//{
	//	GlyphInfo ginf = *gfit;
	//	gid16 gid = ginf.glyphID();
	//	gid = ginf.pseudoGlyphID();

	//	int n = ginf.logicalIndex();
	//	float xy = ginf.origin();
	//	xy = ginf.advanceWidth();
	//	xy = ginf.advanceHeight();
	//	xy = ginf.yOffset();
	//	gr::Rect bb = ginf.bb();
	//	bool f = ginf.isSpace();
	//	f = ginf.insertBefore();
	//	toffset ich = ginf.firstChar();
	//	int ich = ginf.lastChar();
	//	unsigned int dir = ginf.directionality();
	//	dir = ginf.directionLevel();
	//	n = ginf.attachedTo();

	//	n = ginf.numberOfComponents();
	//	for (int i = 0; i < n; i++)
	//	{
	//		bb = ginf.componentBox(i);
	//		ich = ginf.componentFirstChar(i);
	//	}

	//	std::pair<GlyphIterator, GlyphIterator> pairGlyphRange
	//		= pgrseg->charToGlyphs(ginf.firstChar());

	//	for ( ; pairGlyphRange.first != pairGlyphRange.second ; ++(pairGlyphRange.first))
	//	{
	//		ginf = *pairGlyphRange.first;
	//		gid = ginf.glyphID();
	//	}
	//}

	//// for testing:
	//int rgigbb[100];
	//bool rgfClusterStart[100];
	//int cch, cf;
	//pgrseg->getUniscribeClusters(rgigbb, 100, &cch, rgfClusterStart, 100, &cf);

	//// for testing
	//for (int dxWidth = 50; dxWidth < 500; dxWidth += 50)
	//{
	//	int ichBreak;
	//	float dxRetWidth;
	//	ichBreak = pgrseg->findNextBreakPoint(4, klbWsBreak, klbWsBreak, (float)dxWidth, &dxRetWidth, false, false);
	//	int x;
	//	x = 3;
	//}

	pfontSeg->restoreDC();

	// Even if there was an error, if a segment was created, we want to return it.

	if (pgrseg && (*pest != kestNothingFit))
	{
		////qfwgrseg = dynamic_cast<FwGrSegment *>(pgrseg);
		////Assert(qfwgrseg);

		FwGrSegment * psegTmp;
		if (!qfwgrseg)
		{
			psegTmp = NewObj FwGrSegment;
			qfwgrseg = dynamic_cast<FwGrSegment *>(psegTmp);
			Assert(qfwgrseg);
		}
		else
			psegTmp = qfwgrseg.Ptr();

		qfwgrseg->SetGraphiteSegment(pgrseg);

		HRESULT hrTmp;
		CheckHr(hrTmp = qfwgrseg->QueryInterface(IID_ILgSegment, (void **)ppsegRet));
		if (FAILED(hrTmp))
			hr = hrTmp;
		////pgrseg->DecRefCount();
		psegTmp->Release();

		qfwgrseg->SetFwGrEngine(this);
		qfwgrseg->SetTextSource(pgts);

		//pgts->IncRefCount();	// not needed; pgts holds a smart pointer that increments
								// the ref count on the FW text source
	}
	else
	{
		delete pgrseg;
		delete pgts;
		qfwgrseg = NULL;
	}

	return hr;

	END_COM_METHOD(g_fact, IID_IRenderEngine);
}