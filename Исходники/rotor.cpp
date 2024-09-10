LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	HANDLE hPalMem;

	flightstruct *fs = &flights;
	int		x, R,G,B;
	struct elem *pelem;
	
	switch (message)
	{
	case WM_CREATE:
		vLoadStrings();
		GetIniSettings();

		wTimer = SetTimer(hWnd, ID_TIMER, wElapse, NULL);	// create timer for image refresh

		GetClientRect(hWnd, &rc);
		fs->centerx = rc.right / 2;
		fs->centery = rc.bottom / 2;
		fs->smallscrn = (rc.right < 320);

		fs->num = iRotorCnt;

		if (fs->elements == NULL) {							// allocate memory
			if ((fs->elements = (struct elem *)
					malloc(sizeof(struct elem) * fs->num)) == 0) {
						exit(1);
			}
			if ((fs->savex = (LPINT)malloc(sizeof(INT) * iSegLen)) == 0)
					exit(1);
			if ((fs->savey = (LPINT)malloc(sizeof(INT) * iSegLen)) == 0)
					exit(1);
		}
		(void) memset(fs->savex,0, sizeof(fs->savex));

		pelem = fs->elements;

		for (x = fs->num; --x >= 0; pelem++) {			// define drift for segments
			pelem->radius_drift_max = (FLOAT)1.0;
			pelem->radius_drift_now = (FLOAT)1.0;

			pelem->end_radius = (FLOAT)100.0;			// define end radius

			pelem->ratio_drift_max = (FLOAT)1.0;		// define ratio drift
			pelem->ratio_drift_now = (FLOAT)1.0;
			pelem->end_ratio = (FLOAT)10.0;
		}

		srand((unsigned)time(NULL));					// seed random # generator

		fs->rotor = 0;
		fs->prev = 1;
		fs->lastx = fs->centerx;
		fs->lasty = fs->centery;
		fs->angle = (float)(rand() % (long)MAXANGLE) / 3;	// define initial angle
		fs->r = iClrStart;									// set start color value
		fs->firsttime = TRUE;								// first time through

		hPalMem = LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + PALSIZE * sizeof(PALETTEENTRY));
		if (!hPalMem) {
			return -1;
		}
		pLogPal = (NPLOGPALETTE) LocalLock(hPalMem);
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = PALSIZE;
		for (x=0, R=255, G=0, B=0; x < PALSIZE; x++) {
			cycle_colors(&R, &G, &B, 255, 0, 6);

			pLogPal->palPalEntry[x].peRed = LOBYTE(R);
			pLogPal->palPalEntry[x].peGreen = LOBYTE(G);
			pLogPal->palPalEntry[x].peBlue = LOBYTE(B);
			pLogPal->palPalEntry[x].peFlags = PC_RESERVED;
		}
		hPal = CreatePalette((LPLOGPALETTE)pLogPal);
		if (!hPal) {
			return -1;
		}
		break;

	case WM_ERASEBKGND:
        GetClientRect(hWnd,&rc);
		FillRect((HDC)wParam,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
        return 0L;
		break;

	case WM_TIMER:
		MoveImage(hWnd);
		break;
	
	case WM_DESTROY:
		if( wTimer )							// if timer was defined
			KillTimer(hWnd, ID_TIMER);			// then kill it
		free( flights.savey );					// free any allocated memory
		free( flights.savex );
		free( flights.elements );

		if (hPal) {								// free palette memory
			DeleteObject(hPal);
		}
		break;
	}

	return DefScreenSaverProc(hWnd, message, wParam, lParam);
}