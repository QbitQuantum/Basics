void CSyncUsingPil::InitInternal(CParameter& ReceiverParam)
{
	int			i;
	_COMPLEX	cPhaseCorTermDivi;

	/* Init base class for modifying the pilots (rotation) */
	CPilotModiClass::InitRot(ReceiverParam);

	/* Init internal parameters from global struct */
	iNumCarrier = ReceiverParam.iNumCarrier;
	eCurRobMode = ReceiverParam.GetWaveMode();

	/* Check if symbol number per frame has changed. If yes, reset the
	   symbol counter */
	if (iNumSymPerFrame != ReceiverParam.iNumSymPerFrame)
	{
		/* Init internal counter for symbol number */
		iSymbCntFraSy = 0;

		/* Refresh parameter */
		iNumSymPerFrame = ReceiverParam.iNumSymPerFrame;
	}

	/* Allocate memory for histories. Init history with small values, because
	   we search for maximum! */
	vecrCorrHistory.Init(iNumSymPerFrame, -_MAXREAL);

	/* Set middle of observation interval */
	iMiddleOfInterval = iNumSymPerFrame / 2;


#ifdef USE_DRM_FRAME_SYNC_IR_BASED
	/* DRM frame synchronization using impulse response, inits--------------- */
	/* Get number of pilots in first symbol of a DRM frame */
	iNumPilInFirstSym = 0;
	for (i = 0; i < iNumCarrier; i++)
	{
		if (_IsScatPil(ReceiverParam.matiMapTab[0][i]))
			iNumPilInFirstSym++;
	}

	/* Init vector for "test" channel estimation result */
	veccChan.Init(iNumPilInFirstSym);
	vecrTestImpResp.Init(iNumPilInFirstSym);

	/* Init plans for FFT (faster processing of Fft and Ifft commands) */
	FftPlan.Init(iNumPilInFirstSym);

#else

	/* DRM frame synchronization based on time pilots, inits ---------------- */
	/* Allocate memory for storing pilots and indices. Since we do
	   not know the resulting "iNumPilPairs" we allocate memory for the
	   worst case, i.e. "iNumCarrier" */
	vecPilCorr.Init(iNumCarrier);

	/* Store pilots and indices for calculating the correlation. Use only first
	   symbol of "matcPilotCells", because there are the pilots for
	   Frame-synchronization */
	iNumPilPairs = 0;

	for (i = 0; i < iNumCarrier - 1; i++)
	{
		/* Only successive pilots (in frequency direction) are used */
		if (_IsPilot(ReceiverParam.matiMapTab[0][i]) &&
			_IsPilot(ReceiverParam.matiMapTab[0][i + 1]))
		{
			/* Store indices and complex numbers */
			vecPilCorr[iNumPilPairs].iIdx1 = i;
			vecPilCorr[iNumPilPairs].iIdx2 = i + 1;
			vecPilCorr[iNumPilPairs].cPil1 = ReceiverParam.matcPilotCells[0][i];
			vecPilCorr[iNumPilPairs].cPil2 =
				ReceiverParam.matcPilotCells[0][i + 1];

			iNumPilPairs++;
		}
	}

	/* Calculate channel correlation in frequency direction. Use rectangular
	   shaped PDS with the length of the guard-interval */
	const CReal rArgSinc =
		(CReal) ReceiverParam.iGuardSize / ReceiverParam.iFFTSizeN;
	const CReal rArgExp = crPi * rArgSinc;

	cR_HH = Sinc(rArgSinc) * CComplex(Cos(rArgExp), -Sin(rArgExp));
#endif


	/* Frequency offset estimation ------------------------------------------ */
	/* Get position of frequency pilots */
	int iFreqPilCount = 0;
	int iAvPilPos = 0;
	for (i = 0; i < iNumCarrier - 1; i++)
	{
		if (_IsFreqPil(ReceiverParam.matiMapTab[0][i]))
		{
			/* For average frequency pilot position to DC carrier */
			iAvPilPos += i + ReceiverParam.iCarrierKmin;
			
			iPosFreqPil[iFreqPilCount] = i;
			iFreqPilCount++;
		}
	}

	/* Average distance of the frequency pilots from the DC carrier. Needed for
	   corrections for sample rate offset changes. Normalized to sample rate! */
	rAvFreqPilDistToDC =
		(CReal) iAvPilPos / NUM_FREQ_PILOTS / ReceiverParam.iFFTSizeN;

	/* Init memory for "old" frequency pilots */
	for (i = 0; i < NUM_FREQ_PILOTS; i++)
		cOldFreqPil[i] = CComplex((CReal) 0.0, (CReal) 0.0);
	
	/* Nomalization constant for frequency offset estimation */
	rNormConstFOE =
		(CReal) 1.0 / ((CReal) 2.0 * crPi * ReceiverParam.iSymbolBlockSize);

	/* Init time constant for IIR filter for frequency offset estimation */
	rLamFreqOff = IIR1Lam(TICONST_FREQ_OFF_EST, (CReal) SOUNDCRD_SAMPLE_RATE /
		ReceiverParam.iSymbolBlockSize);

	/* Init vector for averaging the frequency offset estimation */
	cFreqOffVec = CComplex((CReal) 0.0, (CReal) 0.0);

	/* Init value for previous estimated sample rate offset with the current
	   setting. This can be non-zero if, e.g., an initial sample rate offset
	   was set by command line arguments */
	rPrevSamRateOffset = ReceiverParam.rResampleOffset;


#ifdef USE_SAMOFFS_TRACK_FRE_PIL
	/* Inits for sample rate offset estimation algorithm -------------------- */
	/* Init memory for actual phase differences */
	for (i = 0; i < NUM_FREQ_PILOTS; i++)
		cFreqPilotPhDiff[i] = CComplex((CReal) 0.0, (CReal) 0.0);

	/* Init time constant for IIR filter for sample rate offset estimation */
	rLamSamRaOff = IIR1Lam(TICONST_SAMRATE_OFF_EST,
		(CReal) SOUNDCRD_SAMPLE_RATE / ReceiverParam.iSymbolBlockSize);
#endif


	/* Define block-sizes for input and output */
	iInputBlockSize = iNumCarrier;
	iMaxOutputBlockSize = iNumCarrier;
}