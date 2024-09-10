BOOL SciEdit::Print(LPCTSTR szTitle)
{
	// Mostly taken from Notepad2 http://www.flos-freeware.ch

	// Don't print empty documents
	if (Call(SCI_GETLENGTH, 0, 0) == 0) {
		return FALSE;
	}

	int startPos;
	int endPos;

	HDC hdc;

	RECT rectMargins;
	RECT rectPhysMargins;
	POINT ptPage;
	POINT ptDpi;

	TEXTMETRIC tm;

	int headerLineHeight;

	int footerLineHeight;
	HFONT fontFooter;

	char dateString[256];

	DOCINFO di = {sizeof(DOCINFO), 0, 0, 0, 0};

	LONG lengthDoc;
	LONG lengthDocMax;
	LONG lengthPrinted;

	struct RangeToFormat frPrint;

	int pageNum;
	BOOL printPage;

	char pageString[32];

	HPEN pen;
	HPEN penOld;

	PRINTDLG pdlg = { sizeof(PRINTDLG), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	pdlg.hwndOwner = GetParent(m_hwndEditor);
	pdlg.hInstance = m_hInst;
	pdlg.Flags = PD_USEDEVMODECOPIES | PD_ALLPAGES | PD_RETURNDC;
	pdlg.nFromPage = 1;
	pdlg.nToPage = 1;
	pdlg.nMinPage = 1;
	pdlg.nMaxPage = 0xffffU;
	pdlg.nCopies = 1;
	pdlg.hDC = 0;
	pdlg.hDevMode = hDevMode;
	pdlg.hDevNames = hDevNames;

	startPos = Call(SCI_GETSELECTIONSTART, 0, 0);
	endPos = Call(SCI_GETSELECTIONEND, 0, 0);

	if (startPos == endPos) {
		pdlg.Flags |= PD_NOSELECTION;
	} else {
		pdlg.Flags |= PD_SELECTION;
	}
	if (1) {
		// Don't display dialog box, just use the default printer and options
		pdlg.Flags |= PD_RETURNDEFAULT;
	}
	if (!PrintDlg(&pdlg)) {
		return TRUE; // False means error...
	}

	hDevMode = pdlg.hDevMode;
	hDevNames = pdlg.hDevNames;

	hdc = pdlg.hDC;

	// Get printer resolution
	ptDpi.x = GetDeviceCaps(hdc, LOGPIXELSX);    // dpi in X direction
	ptDpi.y = GetDeviceCaps(hdc, LOGPIXELSY);    // dpi in Y direction

	// Start by getting the physical page size (in device units).
	ptPage.x = GetDeviceCaps(hdc, PHYSICALWIDTH);   // device units
	ptPage.y = GetDeviceCaps(hdc, PHYSICALHEIGHT);  // device units

	// Get the dimensions of the unprintable
	// part of the page (in device units).
	rectPhysMargins.left = GetDeviceCaps(hdc, PHYSICALOFFSETX);
	rectPhysMargins.top = GetDeviceCaps(hdc, PHYSICALOFFSETY);

	// To get the right and lower unprintable area,
	// we take the entire width and height of the paper and
	// subtract everything else.
	rectPhysMargins.right = ptPage.x            // total paper width
		- GetDeviceCaps(hdc, HORZRES) // printable width
		- rectPhysMargins.left;        // left unprintable margin

	rectPhysMargins.bottom = ptPage.y            // total paper height
		- GetDeviceCaps(hdc, VERTRES)  // printable height
		- rectPhysMargins.top;        // right unprintable margin

	// At this point, rectPhysMargins contains the widths of the
	// unprintable regions on all four sides of the page in device units.

	rectMargins.left  = rectPhysMargins.left;
	rectMargins.top  = rectPhysMargins.top;
	rectMargins.right  = rectPhysMargins.right;
	rectMargins.bottom  = rectPhysMargins.bottom;

	// rectMargins now contains the values used to shrink the printable
	// area of the page.

	// Convert device coordinates into logical coordinates
	DPtoLP(hdc, (LPPOINT)&rectMargins, 2);
	DPtoLP(hdc, (LPPOINT)&rectPhysMargins, 2);

	// Convert page size to logical units and we're done!
	DPtoLP(hdc, (LPPOINT) &ptPage, 1);

	// Leave blank
	headerLineHeight = 0;

	footerLineHeight = MulDiv(7,ptDpi.y, 72);
	fontFooter = CreateFont(footerLineHeight,
		0, 0, 0,
		FW_NORMAL,
		0,
		0,
		0, 0, 0,
		0, 0, 0,
		"Arial");
	SelectObject(hdc, fontFooter);
	GetTextMetrics(hdc, &tm);
	footerLineHeight = tm.tmHeight + tm.tmExternalLeading;

	di.lpszDocName = szTitle;
	di.lpszOutput = 0;
	di.lpszDatatype = 0;
	di.fwType = 0;
	if (StartDoc(hdc, &di) < 0) {
		DeleteDC(hdc);
		if (fontFooter)
			DeleteObject(fontFooter);
		return FALSE;
	}

	// Get current date...
	SYSTEMTIME st;
	GetLocalTime(&st);
	GetDateFormat(LOCALE_USER_DEFAULT,DATE_SHORTDATE,&st,NULL,dateString,256);

	// Set print color mode
	int printColorModes[5] = {
		SC_PRINT_NORMAL,
		SC_PRINT_INVERTLIGHT,
		SC_PRINT_BLACKONWHITE,
		SC_PRINT_COLOURONWHITE,
		SC_PRINT_COLOURONWHITEDEFAULTBG };
	Call(SCI_SETPRINTCOLOURMODE, printColorModes[0], 0);

	// Set print zoom...
	Call(SCI_SETPRINTMAGNIFICATION, (WPARAM)0, 0);

	lengthDoc = Call(SCI_GETLENGTH, 0, 0);
	lengthDocMax = lengthDoc;
	lengthPrinted = 0;

	// Requested to print selection
	if (pdlg.Flags & PD_SELECTION) {
		if (startPos > endPos) {
			lengthPrinted = endPos;
			lengthDoc = startPos;
		} else {
			lengthPrinted = startPos;
			lengthDoc = endPos;
		}

		if (lengthPrinted < 0)
			lengthPrinted = 0;
		if (lengthDoc > lengthDocMax)
			lengthDoc = lengthDocMax;
	}

	// We must substract the physical margins from the printable area
	frPrint.hdc = hdc;
	frPrint.hdcTarget = hdc;
	frPrint.rc.left = rectMargins.left - rectPhysMargins.left;
	frPrint.rc.top = rectMargins.top - rectPhysMargins.top;
	frPrint.rc.right = ptPage.x - rectMargins.right - rectPhysMargins.left;
	frPrint.rc.bottom = ptPage.y - rectMargins.bottom - rectPhysMargins.top;
	frPrint.rcPage.left = 0;
	frPrint.rcPage.top = 0;
	frPrint.rcPage.right = ptPage.x - rectPhysMargins.left - rectPhysMargins.right - 1;
	frPrint.rcPage.bottom = ptPage.y - rectPhysMargins.top - rectPhysMargins.bottom - 1;
	frPrint.rc.top += headerLineHeight + headerLineHeight / 2;
	frPrint.rc.bottom -= footerLineHeight + footerLineHeight / 2;
	// Print each page
	pageNum = 1;

	WaitCursor wait;
	while (lengthPrinted < lengthDoc) 
	{
		printPage = (!(pdlg.Flags & PD_PAGENUMS) ||
			(pageNum >= pdlg.nFromPage) && (pageNum <= pdlg.nToPage));

		sprintf_s(pageString, "Page %d", pageNum);

		if (printPage) 
		{
			StartPage(hdc);

			SetTextColor(hdc, RGB(0,0,0));
			SetBkColor(hdc, RGB(255,255,255));
			UINT ta = SetTextAlign(hdc, TA_BOTTOM);
			RECT rcw = {frPrint.rc.left, frPrint.rc.top - headerLineHeight - headerLineHeight / 2,
				frPrint.rc.right, frPrint.rc.top - headerLineHeight / 2};
			rcw.bottom = rcw.top + headerLineHeight;
	    }

		frPrint.chrg.cpMin = lengthPrinted;
		frPrint.chrg.cpMax = lengthDoc;

		lengthPrinted = Call(SCI_FORMATRANGE, printPage, (LPARAM)&frPrint);

		if (printPage) {
			SetTextColor(hdc, RGB(0,0,0));
			SetBkColor(hdc, RGB(255,255,255));
			SelectObject(hdc, fontFooter);
			UINT ta = SetTextAlign(hdc, TA_TOP);
			RECT rcw = {frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 2,
				frPrint.rc.right, frPrint.rc.bottom + footerLineHeight + footerLineHeight / 2};

			// Frint Footer Page num
			SIZE sizeFooter;
			GetTextExtentPoint32(hdc,pageString,lstrlen(pageString),&sizeFooter);
			ExtTextOut(hdc, frPrint.rc.right - 5 - sizeFooter.cx, frPrint.rc.bottom + footerLineHeight / 2,
				/*ETO_OPAQUE*/0, &rcw, pageString,
			lstrlen(pageString), NULL);

			SetTextAlign(hdc, ta);
			pen = ::CreatePen(0, 1, RGB(0,0,0));
			penOld = (HPEN)SelectObject(hdc, pen);
			SetBkColor(hdc, RGB(0,0,0));
			MoveToEx(hdc, frPrint.rc.left, frPrint.rc.bottom + footerLineHeight / 4, NULL);
			LineTo(hdc, frPrint.rc.right, frPrint.rc.bottom + footerLineHeight / 4);
			SelectObject(hdc, penOld);
			DeleteObject(pen);

			EndPage(hdc);
		}
		pageNum++;

		if ((pdlg.Flags & PD_PAGENUMS) && (pageNum > pdlg.nToPage))
			break;
	}

	Call(SCI_FORMATRANGE, FALSE, 0);

	EndDoc(hdc);
	DeleteDC(hdc);
	if (fontFooter)
		DeleteObject(fontFooter);

	return TRUE;
}