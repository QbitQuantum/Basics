bool MYDISP::begin() {
	HBMP	hbmp;
	int		cntInit;
	int		ibtn;
	int		ifng;

	/* If we have already been initialized successfully, just return true;
	*/
	if (fInitialized) {
		return fInitialized;
	}

	/* Attempt to initialize the MTDS library.
	*/
	cntInit = 10;
	while (true) {
		if (mtds.begin()) {
			break;
		}

		if (--cntInit <= 0) {
			return false;
		}

#if !defined(__SIM__)
		delay(1000);
#endif
	}

	/* Get the DS objects that we will use and set up the default values.
	*/
	if ((hdsDisp = mtds.GetDs()) == 0) {
		return false;
	}
	hbmp = mtds.GetDisplayBitmap();
	mtds.SetDrawingSurface(hdsDisp, hbmp);

	if ((hdsBlt = mtds.GetDs()) == 0) {
		mtds.ReleaseDs(hdsDisp);
		return false;
	}

	idBtnTrack = -1;
	clrFg = clrWhite;
	clrBg = clrBlack;
	clrTr = clrBlack;
	bkCur = bkOpaque;
	penCur = penSolid;
	ityCur = 100;

	mtds.SetFgColor(hdsDisp, clrFg);
	mtds.SetBgColor(hdsDisp, clrBg);
	mtds.SetTransColor(hdsDisp, clrTr);
	hbrFg = mtds.CreateSolidBrush(clrFg);
	mtds.SetPen(hdsDisp, penCur);
	mtds.SetDrwRop(hdsDisp, drwCopyPen);
	mtds.SetBkMode(hdsDisp, bkCur);
	mtds.SetFont(hdsDisp, hfntConsole);
	mtds.SetIntensity(hdsDisp, ityCur);

	/* Initialize the button array.
	*/
	for (ibtn = 0; ibtn < NUM_BUTTONS; ibtn++) {
		rgbtn[ibtn].fs = 0;
		rgbtn[ibtn].hbmpUp = 0;
		rgbtn[ibtn].hbmpDn = 0;
		rgbtn[ibtn].hbmpBg = 0;
	}

	/* Initialize the finger activity array.
	*/
	for (ifng = 0; ifng < 2; ifng++) {
		rgfng[ifng].st = FINGER_UP;
		rgfng[ifng].x = -1;
		rgfng[ifng].y = -1;
	}

	fInitialized = true;
	return fInitialized;

}