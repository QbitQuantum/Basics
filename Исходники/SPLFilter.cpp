int _tmain(int argc, _TCHAR* argv[])
{
	// Before we can do anything, we need to unlock the DLL
	// NOTE: If you are evaluating FOXIT READER SDK, you don’t need unlock the DLL,
	// then evaluation marks will be shown with all rendered pages.
	FPDF_UnlockDLL("license_id", "unlock_code");

	// first, load the document (no password specified)
	pdf_doc = FPDF_LoadDocument("testdoc.pdf", NULL);

	// error handling
	if (pdf_doc == NULL) 
	{
		fprintf(stderr, "ERROR - doc\n");
		exit(1);
	}

	// Open the out file
	
	fopen_s(&out, "test.spl", "wb");

	// Send the StartDoc header
	
	wchar_t* dname = L"desktop.ini - Editor";
	wchar_t* prn = L"c:\\output.prn";
	
	{

	if (wcsnlen(dname, 255) == 255)
		ErrorExit(L"dname too long");
	if (wcsnlen(prn, 255) == 255)
		ErrorExit(L"prn too long");

	SPL_HEADER spl;

	spl.SIGNATURE=SPLMETA_SIGNATURE;
	spl.nSize=(DWORD)sizeof(spl)+wcslen(dname)*2+wcslen(prn)*2+4; // +4, because \0\0 is after dname and prn
	spl.offDocumentName=(DWORD)sizeof(spl);
	spl.offPort=(DWORD)sizeof(spl)+wcslen(dname)*2+2; // +2 because \0\0 is after dname
	
	fwrite(&spl, sizeof(spl), 1, out);
	
	fwrite(dname, wcslen(dname)*2, 1, out);
	fwrite("\0\0", 2, 1, out);

	fwrite(prn, wcslen(prn)*2, 1, out);
	fwrite("\0\0", 2, 1, out);
	}

	// Load the first page and calculate the bbox
	// based on the printer margins

	pdf_page = FPDF_LoadPage(pdf_doc, 0);
	if (pdf_page == NULL)
		ErrorExit(L"FPDF_LoadPage");

	double page_width, page_height;
    
	page_width = FPDF_GetPageWidth(pdf_page);
    page_height = FPDF_GetPageHeight(pdf_page);

#ifdef EXT_PRINT
#ifdef EXT_PRNDLG
	PRINTDLG pd;
	HWND hwnd = NULL;

	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = hwnd;
	pd.hDevMode    = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames
	pd.Flags       = PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC; 
	pd.nCopies     = 1;
	pd.nFromPage   = 0xFFFF; 
	pd.nToPage     = 0xFFFF; 
	pd.nMinPage    = 1; 
	pd.nMaxPage    = 0xFFFF; 
	

	if (PrintDlg(&pd) != TRUE)
		ErrorExit(L"PrintDialog\n");

	hDC = pd.hDC;
#else
	wchar_t* printer=L"FF";
	if (!OpenPrinter(printer, &hPrinter, NULL))
		ErrorExit(L"OpenPrinter\n");
    DWORD dwNeeded = DocumentProperties(NULL, hPrinter, printer, NULL, NULL, 0);
    lpDevMode = (LPDEVMODE)malloc(dwNeeded);
	
	DocumentProperties(NULL, hPrinter, printer, lpDevMode, NULL, DM_OUT_BUFFER);
	/* Try to set a higher print quality */
	lpDevMode->dmPrintQuality=1200;
	lpDevMode->dmFields|=DM_PRINTQUALITY;
	DocumentProperties(NULL, hPrinter, printer, lpDevMode, lpDevMode, DM_IN_BUFFER | DM_OUT_BUFFER);
#ifdef EXT_PRNOPTS
	DocumentProperties(NULL, hPrinter, printer, lpDevMode, lpDevMode, DM_IN_BUFFER | DM_PROMPT | DM_OUT_BUFFER);
#endif
	hDC = CreateDC(L"WINEPS.DRV", printer, NULL, lpDevMode);

	ClosePrinter(&hPrinter);
#endif
#else
	hDC = CreateDC(L"WINEPS.DRV", L"FF", NULL, lpDevMode);
#endif

	
#ifdef PRINT
	DOCINFO doc_info;

	doc_info.cbSize=sizeof(DOCINFO)+12;
	doc_info.lpszDocName=dname;
	doc_info.lpszOutput=prn;
	doc_info.lpszDatatype=NULL;
	doc_info.fwType=0;

	// Start a printer job
	StartDoc(hDC, &doc_info);
#endif
	
	// get number of pixels per inch (horizontally and vertically)
	logpixelsx = GetDeviceCaps(hDC, LOGPIXELSX);
	logpixelsy = GetDeviceCaps(hDC, LOGPIXELSY);
	
	// convert points into pixels
	size_x = (int)page_width / 72 * logpixelsx;
	size_y = (int)page_height / 72 * logpixelsy;

	DWORD p_width =GetDeviceCaps(hDC, HORZSIZE)*100;
	DWORD p_height=GetDeviceCaps(hDC, VERTSIZE)*100;

	SetRect( &rect, 0, 0, p_width, p_height );

#ifdef DEBUG
	//fprintf(stderr, "x=%u, y=%u, pw=%u, ph=%u,sx=%u,sy=%u,lpx=%u,lpy=%u,size_x=%u,size_y=%u\n",x,y,page_width,page_height,sx,sy,logpixelsx,logpixelsy,size_x,size_y);
#endif

	// now load the pages one after another

	for (i=0; i < FPDF_GetPageCount(pdf_doc); i++)
	{
#ifdef DEBUG
		fprintf(stderr, "Load page %d/%d\n", i, FPDF_GetPageCount(pdf_doc));
#endif

		// Load the next page

		pdf_page = FPDF_LoadPage(pdf_doc, i);
		
		if (pdf_page == NULL)
			ErrorExit(L"FPDF_LoadPage");
	
		fbuf=NULL;
#ifdef DEBUG
		sprintf_s(buf, 255, "test-%d.emf", i);
		//fbuf=buf;
#endif

		// Create a metafile to render to

		hMeta = CreateEnhMetaFileA(hDC, 
	          fbuf, 
	          &rect, "SPLFilter.exe\0Created by Fabian\0\0");

		if (hMeta == NULL)
			ErrorExit(L"CreateEnhMetaFileA");

	 	// Call FPDF_RenderPage function to render the whole page
		FPDF_RenderPage(hMeta, pdf_page, 0, 0, size_x, size_y, 0, 0);

#ifdef PRINT
		// Start a new printing page
		StartPage(hDC);
		FPDF_RenderPage(hDC, pdf_page, 0, 0, size_x, size_y, 0, 0);
		EndPage(hDC);
#endif

		// Close PDF page

		FPDF_ClosePage(pdf_page);

		efile=CloseEnhMetaFile(hMeta);

		if (efile == NULL)
			ErrorExit(L"CloseEnhMetaFile");

		// Write EMF data - via enumeration, because we want to embed fonts later
	    EnumEnhMetaFile(hDC, efile, enum_it, NULL, &rect);

		// Write EndPage() record
		{
		SMR_EOPAGE smr_eopage;
		
		smr_eopage.smrext.smr.iType=SRT_EXT_EOPAGE_VECTOR;
		smr_eopage.smrext.smr.nSize=sizeof(smr_eopage)-sizeof(smr_eopage.smrext.smr);

		/* FIXME: Need to calcualte low and high correctly */
		smr_eopage.smrext.DistanceLow=bufSize+smr_eopage.smrext.smr.nSize;
		smr_eopage.smrext.DistanceHigh=0;

		fwrite(&smr_eopage, sizeof(smr_eopage), 1, out);
		}
		
		DeleteEnhMetaFile(efile);
	}
#ifdef PRINT
	EndDoc(hDC);
#endif

	fclose(out);
	out=NULL;
	DeleteDC(hDC);
	FPDF_CloseDocument(pdf_doc);

#ifdef DEBUG
	fprintf(stderr, "SPLFilter: Conversion successful!\n");
#endif
	exit(0);
}