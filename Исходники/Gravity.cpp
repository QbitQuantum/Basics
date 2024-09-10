LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	RECT	rc;
	HANDLE	hPalMem;	

    switch (msg)
    {                
        case WM_CREATE:
        {
			gravstruct	*gp = &gravs;
        	int		i, R,G,B;
			unsigned char ball;

			vLoadStrings();					// load strings from table
			GetIniSettings();				// get settings from ini file (control.ini)
        	
            wTimer = SetTimer(hWnd, ID_TIMER, wElapse, NULL);	// create timer to move image
                        
            GetClientRect(hWnd, &rc);							// find size of screen
			gp->width = rc.right;
			gp->height = rc.bottom;

			gp->sr = STARRADIUS;

			gp->nplanets = iPlanets;
			srand((unsigned)time(NULL));	// seed random w/ timer

			if (!gp->planets) {
				gp->planets = (planetstruct*)malloc((gp->nplanets+1)*sizeof(planetstruct));
				memset(gp->planets, 0, (gp->nplanets+1)*sizeof(planetstruct));
				gp->starcolor = rand() % (PALSIZE-21);
			}

			for (ball = 0; ball <= gp->nplanets; ball++)
				init_planet(&(gp->planets[ball]));

			// Create a logical palette to play with
			hPalMem = LocalAlloc(LMEM_FIXED,
								sizeof(LOGPALETTE)
								+ PALSIZE * sizeof(PALETTEENTRY));
			if (!hPalMem) {
				// error("No memory for palette");
				return -1;
			}
			pLogPal = (NPLOGPALETTE) LocalLock(hPalMem);
			pLogPal->palVersion = 0x300;
			pLogPal->palNumEntries = PALSIZE;
	        for (i=0, R=255,G=0,B=0; i<PALSIZE; i++) {
	        
	        	cycle_colors(&R,&G,&B,255,0,6);
	        	
	            pLogPal->palPalEntry[i].peRed = LOBYTE(R);
	            pLogPal->palPalEntry[i].peGreen = LOBYTE(G);
	            pLogPal->palPalEntry[i].peBlue = LOBYTE(B);
	            pLogPal->palPalEntry[i].peFlags = PC_RESERVED;
	        }
	        hPal = CreatePalette((LPLOGPALETTE)pLogPal);
	        if (!hPal) {
	            //Error("CreatePalette() failed");
	            return -1;
	        }
			break;
        }
        
        case WM_TIMER:                              // BOUNCER-specific
            MoveImage(hWnd);						// move image around
            break;

        case WM_DESTROY:                            // BOUNCER-specific
            if( wTimer )
            	KillTimer(hWnd, ID_TIMER);
			if (hPal)
				DeleteObject(hPal);
			free(gravs.planets);            
            break;

        case WM_ERASEBKGND:
			GetClientRect(hWnd,&rc);
			FillRect((HDC)wParam,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
            return 0L;

        default:
            break;
        }

    return DefScreenSaverProc(hWnd, msg, wParam, lParam);
}