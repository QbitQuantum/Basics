/******************************************************************************
 * FontEditCommand(hBox, id)
 *
 * purpose: interprets menu id and calls appropriate function to do the task
 *
 * params:  HWND hBox : handle to main window
 *          WORD id   : menu command id
 * returns: none
 *
 * side effects: plenty
 *
 *****************************************************************************/
VOID
FontEditCommand(
	HWND hBox,
	WORD id
	)
{
	CHAR * szError;                 /* String for error messages */
	LONG w; 
	DWORD y, i, j;
	BOOL fRepaint = FALSE;
	HMENU hMenu;
	DLGPROC lpprocAboutDlg;
	MSG message;

	szError = "";               /* No Errors yet */

	switch (id) {
	    case FONT_EXIT:
		if (!CheckSave())    /* See if any files need saving */
			break;
		/* Window's being destroyed. */
		if (fLoaded)         /* 4/8/87 Linsh added */
			DeleteBitmap(); /* Get rid of memory DC */
		PostQuitMessage(0);  /* Cause application to be terminated */
                break;

            case FONT_HELP_CONTENTS:
                WinHelp(hFont, gszHelpFile, HELP_CONTENTS, 0L);
                break;

            case FONT_HELP_SEARCH:
                /*
                 * Tell winhelp to be sure this app's help file is current,
                 * then invoke a search with an empty starting key.
                 */
                WinHelp(hFont, gszHelpFile, HELP_FORCEFILE, 0);
                WinHelp(hFont, gszHelpFile, HELP_PARTIALKEY, (DWORD)(LPSTR)"");
                break;

	    case FONT_ABOUT:
		lpprocAboutDlg = (DLGPROC)AboutDlg;
		DialogBox (hInst, vszABOUT, hBox, lpprocAboutDlg);
		FreeProcInstance (lpprocAboutDlg);
		break;

	    case FONT_LOAD:             /*  Check File Name  */
	    case FONT_NEW :
		if (!CheckSave())       /*  See if current font needs saving */
			return;
	/* to prevent scrambling of Show window chars, Bring back Show
        ** window to parent window's client area before invoking the dialog */

		if (CommDlgOpen(hBox,&ofstrFile,szNewFile,szExt,szFontFile,id)
				== FALSE) {

			InvalidateRect(hFont, (LPRECT)NULL, FALSE);
			UpdateWindow(hFont);
			return;
		}
		/* else drop thru */

	    case FONT_START:	/*  Here if file name passed as argument */
		InvalidateRect(hFont, (LPRECT)NULL, FALSE);
		UpdateWindow(hFont);

		szError = FontLoad (szNewFile, &ofstrFile);

	/* Hack : needed to remove umwanted WM_MOUSEMOVE messages from the 
         * queue.
         * Apparently, Windows needs to reposition the mouse after a dialog
         * is ended with a mouse double-click (releases mouse capture?) for
         * which a couple of WM_MOUSEMOVEs may get sent to parent app.
         * These mess with the edit box below the dialog if they happen to 
         * overlap.
         */
		PeekMessage((LPMSG) &message, hBox, WM_MOUSEMOVE, WM_MOUSEMOVE,
		    PM_REMOVE);

		if (fLoaded)    /* If loaded then do a few things */ {
		    jChar = iChar = 65;                 /* Show an A */
		    if ((BYTE)iChar > (BYTE)font.LastChar)
			jChar = iChar = font.FirstChar; /* .. if we can */
		    swH = 15;                   /* Good bet to make A visible */
		    fEdited = fChanged = FALSE;
		    ResizeShow();               /* Set Box to proper size */
		    ScrollFont();               /* Set thumb */
		    CharToBox(iChar);
		}
		FontRename(szError);
		SetFocus(hBox);
		return;

	    case FONT_SAVE:
		if (!NewFile) {
		    if (fLoaded && fChanged) {
			lstrcpy((LPSTR)szNewFile, (LPSTR)szFontFileFull);
			BoxToChar(iChar);           /* Just in case */
			szError = FontSave (szNewFile, &ofstrFile);
			FontRename(szError);        /* Rename or Print Error */
			return;
		    }
		    else
			return;
		}
	/* else file has been opened by selecting NEW... on menu.
         * Fall thro' and bring up SaveAs dialog minus default
         * filename in edit window */

	    case FONT_SAVEAS:
		BoxToChar(iChar);               /* Just in case */

		if (CommDlgSaveAs (hInst, hBox, &ofstrFile, szNewFile, szExt,
				szFontFile) == TRUE) {

		    szError = FontSave (szNewFile, &ofstrFile);
		    FontRename (szError);          /* Rename or Print Error */
		}

		/* to prevent scrambling of Show window chars,
           repaint show window after dialog is brought down */
		InvalidateRect (hFont, (LPRECT)NULL, TRUE);
		UpdateWindow (hFont);
		return;

	    case FONT_HEADER:
		/* to prevent scrambling of Show window chars,
		 * repaint show window after dialog is invoked */
		DialogBox(hInst, (LPSTR)vszDHeader, hBox, lpHeaderProc);
		InvalidateRect(hFont, (LPRECT)NULL, TRUE);
		UpdateWindow(hFont);
		return;

	    case FONT_RESIZE:
		/* to prevent scrambling of Show window chars,
		   repaint show window after dialog is brought down */
		if (DialogBox(hInst, (LPSTR)vszDResize, hBox, lpReSizeProc)) {
		    /* BoxToChar(iChar);*/ /* save current before resizing */
		    ResizeShow();       /* New Font Display Size */
		    CharToBox(iChar);               /* New Box display */
		}
		InvalidateRect(hFont, (LPRECT)NULL, TRUE);
		UpdateWindow(hFont);
		return;

	    case FONT_COPY:                     /* Copy to Clipboard */
		BoxToChar(iChar);               /* Just in case */
		ToClipboard(iChar, wBox, kBox);
		break;

	    case FONT_PASTE:            /* Paste in Character form Clipboard */
		BoxBackup();            /* In case we change our minds */
		ptA.x = ptA.y = 0;
		wBox = ClipboardToBox(ptA, wBox, kBox, TRUE);
		fRepaint = TRUE;
		break;

	    case WIDER_LEFT:
	    case WIDER_RIGHT:
	    case WIDER_BOTH:
	    case NARROWER_LEFT:
	    case NARROWER_RIGHT:
	    case NARROWER_BOTH:
	    case WIDTH:
		w = newWidth = wBox;
		if (font.Family & 1)            /* Variable width or else */ {
		    switch (id) {
			case WIDER_BOTH:
			    w++;
			case WIDER_LEFT:
			case WIDER_RIGHT:
			    w++;
			    break;
			case NARROWER_BOTH:
			    w--;
			case NARROWER_LEFT:
			case NARROWER_RIGHT:
			    w--;
			    break;
			case WIDTH:
			    if (DialogBox(hInst,
					(LPSTR)vszDWidth, hBox, lpWidthProc))
				w = newWidth;
			    break;
		    }

		    if (w < 0 || w >= wBoxLim) {
			MessageBox(hBox,
				(LPSTR)vszEdLimits0To64,
				(LPSTR)szAppName,
				MB_OK | MB_ICONASTERISK);
			break;                  /* Out of range! quit */
		    }
		    if (w > (LONG) font.MaxWidth) {
			if (IDOK == MessageBox(hBox,
					    (LPSTR)vszMaxWidthIncrease,
					    (LPSTR)szAppName,
					    MB_OKCANCEL | MB_ICONQUESTION))
			    font.MaxWidth = (WORD)w;
			else
			    break;
		    }
		    BoxBackup();                /* In case we change our minds */
		    wBox = (WORD)w;             /* Reset width */
		    fRepaint = TRUE;            /* Signal redraw */
		    switch (id) {
		    case WIDER_LEFT:
#ifdef DBCS	//DBCS_FIX
			DupCol(0, kBoxLim - 1);
			for (y = 0; y < kBoxLim; y++)
			    matBox[0][y] = FALSE;       /* Clear left column */
			break;
#endif
		    case WIDER_BOTH:            /* Shift character one right */
			DupCol(0, kBoxLim - 1);
			for (y = 0; y < kBoxLim; y++)
			    matBox[wBox -1][y] = FALSE; /* Clear right column */
			for (y = 0; y < kBoxLim; y++)
			    matBox[0][y] = FALSE;       /* Clear left column */
			break;
		    case NARROWER_LEFT:
		    case NARROWER_BOTH:	/* Shift character one left */
			if (wBox) {	/* .. unless width is already 0 */
			    for (j = 0; j <= kBox - 1; j++)
				for (i = 0; i <= wBox - 1; i++)
				    matBox[i][j] = matBox[i + 1][j];
			    break;
			}
		    }
		}
		else {
		    MessageBox(hBox,
			    (LPSTR)vszCannotChangeWidth,
			    (LPSTR)szAppName,
			    MB_OK | MB_ICONASTERISK);
		}
		break;

	    case ROW_ADD:
	    case ROW_DEL:
	    case COL_ADD:
	    case COL_DEL:
		/* set cursor to "+" shaped cursor */
		SetCapture (hBox); /* so that cursor doesn't get restored
				      before we are done */
		hOldCursor = SetCursor (LoadCursor (NULL, IDC_CROSS));
		fCaptured = TRUE;
		cursor = id;
		break;

	    case BOX_CLEAR:
	    case BOX_FILL:
	    case BOX_INV:
	    case BOX_HATCH:
	    case BOX_LEFTRIGHT:
	    case BOX_TOPBOTTOM:
	    case BOX_COPY:
	    case BOX_PASTE:
		/* Get one o' da funky cursors */
		SetCapture(hBox);
		hOldCursor = SetCursor(LoadCursor(hInst, MAKEINTRESOURCE(id)));
		fStartRubberBand = TRUE;
		CharRectDimensions((LPRECT)&FontRect);
		cursor = id;
		break;

	    case BOX_REFRESH:           /* Go get old version of character */
		BoxBackup();            /* In case we change our minds */
		CharToBox(iChar);
		hMenu = GetMenu(hBox);
		EnableMenuItem(hMenu, BOX_UNDO, MF_ENABLED);    /* Can Unrefresh! */
		break;
	    case BOX_UNDO:
		BoxRestore();
		hMenu = GetMenu(hBox);
		EnableMenuItem(hMenu, BOX_REFRESH, MF_ENABLED);
		fRepaint = TRUE;
		break;
	}
	if (fRepaint) {
		fEdited = fChanged = TRUE;
		InvalidateRect(hBox, (LPRECT)NULL, TRUE);
	}
}