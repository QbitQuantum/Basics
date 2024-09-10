/********************************************************************
* Function : SimLoop()
* Purpose : Performs a single Simulation Loop iteration. Includes
*           drawing.
********************************************************************/
int SimLoop(void)
{
	static int nFramesPerSecond = 0;
	static int nFramesSinceLastTick;
	static DWORD LastTicks = 0;
	DWORD Ticks;
	HDC hDC;
	HFONT hOldFont;
	char s[80];
	int slen;

	DDSURFACEDESC ddsd;
	DDBLTFX	BltFx;
	HRESULT ddreturn;

	/* Perform a single step in our world. */
	if (StepWorld(bForwardKey, bBackKey, bLeftKey, bRightKey, nState, nGauge))
	{
		if (lpPrimary->IsLost() == DDERR_SURFACELOST)
			lpPrimary->Restore();

		/* Clear the backbuffer. */
#if CLEARBCKGRND
		BltFx.dwSize = sizeof(BltFx);
		BltFx.dwFillColor = 255;
		ddreturn = lpBackbuffer->Blt(NULL,
											  NULL,
											  NULL,
											  DDBLT_COLORFILL | DDBLT_WAIT,
											  &BltFx);
#else
		ddreturn = DD_OK;
#endif
		if (ddreturn == DD_OK)
		{	/* While this is running, prepare
			 * the drawing. */
			if (PrepDrawWorld())
			{
				/* Lock the surface. */
				memset(&ddsd, 0, sizeof(DDSURFACEDESC));
				ddsd.dwSize = sizeof(ddsd);
				ddreturn = lpBackbuffer->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_SURFACEMEMORYPTR, NULL);
				if (ddreturn == DD_OK)
				{
					DrawWorld((unsigned char *)ddsd.lpSurface, (int)ddsd.lPitch);

					int nX, nY;
					static unsigned char dummy;
					unsigned char ni;
					ni = 0;
					for (nY = 0; nY < 16; nY++)
						for (nX = 0; nX < 16; nX++)
						{
							/* Draw a small block at (nX * 3, nY * 3) */
							((unsigned char *)ddsd.lpSurface)[(nY * 3 * ddsd.lPitch) + (nX * 3)] = ni;
							((unsigned char *)ddsd.lpSurface)[(nY * 3 * ddsd.lPitch) + (nX * 3 + 1)] = ni;
							((unsigned char *)ddsd.lpSurface)[((nY * 3 + 1) * ddsd.lPitch) + (nX * 3)] = ni;
							((unsigned char *)ddsd.lpSurface)[((nY * 3 + 1) * ddsd.lPitch) + (nX * 3 + 1)] = ni;
							ni++;
						}
					lpBackbuffer->Unlock(NULL);

					/* And now write Frames per second. */
					/* Increment Frame counter. */
					nFramesSinceLastTick++;
					/* Get system tick count. */
					Ticks = GetTickCount();
					/* Update fps value every second. */
					if (Ticks > (LastTicks + 1000))
					{	nFramesPerSecond = nFramesSinceLastTick;
						nFramesSinceLastTick = 0;
						LastTicks = Ticks;
					}

					/* Get a DC to the buffer & write count. */
					if (DD_OK == lpBackbuffer->GetDC(&hDC))
					{	
						SetBkMode(hDC, TRANSPARENT);
						hOldFont = SelectObject(hDC, AppFont);
						/* Build a string for display. */
						slen = wsprintf(s, "FPS : %d", nFramesPerSecond);
						/* And draw the text. */
						SetTextColor(hDC, RGB(0,0,0));
						SIZE sz;
						GetTextExtentPoint32(hDC, s, slen, &sz);
						RECT rc;
						rc.top = 0;
						rc.left = 16 * 3;
						rc.right = 16 * 3 + sz.cx + 10;
						rc.bottom = sz.cy + 10;
						DrawFrameControl(hDC, &rc, DFC_BUTTON, DFCS_BUTTONPUSH);
						TextOut(hDC, 16*3 + 5, 5, s, slen);
						SelectObject(hDC, hOldFont);
						lpBackbuffer->ReleaseDC(hDC);
					}
					/* Perform required pageflipping to make the surface
					 * we drawed visible. */
					ddreturn = lpPrimary->Flip(NULL, DDFLIP_WAIT);
					if (ddreturn == DD_OK)
					{
						return 1;
					}
				} 
			}
		}
	}

	return 0;
}