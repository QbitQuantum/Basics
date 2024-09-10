BOOL CDrawDoc::StoreForPrinting(CArchive& ar)
{
	// setting up EMF DC, using default printer as reference	
	HDC hPrt = ((CDrawApp*)AfxGetApp()) -> GetDefaultPrinterIC() ;
	if (!hPrt) return FALSE;
	RECT rect={0, 0, GetDeviceCaps(hPrt,HORZSIZE)*100, GetDeviceCaps(hPrt,VERTSIZE)*100};
	CDC dc;
	if (! (dc.m_hDC = CreateEnhMetaFile(hPrt, NULL, &rect, NULL))) return FALSE;
	dc.SetAttribDC(dc.m_hDC);

	// recording meta file
	POSITION pos = GetFirstViewPosition();
	CDrawView* pView = (CDrawView*)GetNextView(pos);
	if (pView == NULL) return FALSE;
	CDrawView::m_IsRecording = TRUE;
	pView -> OnPrepareDC(&dc, NULL);
	Draw(&dc, pView);
	CDrawView::m_IsRecording = FALSE;             
	HENHMETAFILE hEmf = CloseEnhMetaFile(dc.m_hDC);

	// storing EMF into archive
	DWORD size = GetEnhMetaFileBits(hEmf, NULL, NULL);
	if (size == 0) return FALSE;
	HGLOBAL hglobal = GlobalAlloc(GMEM_MOVEABLE, size);
	if (hglobal == NULL) return FALSE;
	LPBYTE buf = (LPBYTE)GlobalLock(hglobal);
	if (buf == NULL) return FALSE;
	if (GetEnhMetaFileBits(hEmf,size,buf) != size) return FALSE;

	SEPFILEHEADER header;

	// set EMF size (header)
	header.dwEmfSize = size;

	// get text objects count
	pos = m_objects.GetHeadPosition();
	DWORD count=0;
	while (pos != NULL)
		{
		CDrawText* pObj = (CDrawText*)(m_objects.GetNext(pos));
		if (pObj->GetLogFontCopy() != NULL)	
			count++;
		}
	// set text records (header)
	header.dwTextRecords = count;

	// set page size (in logical) (header)
	header.sizePage = GetSize();

	// write header
	ar.Write(&header,sizeof(SEPFILEHEADER));

	// write EMF into archive
	ar.Write(buf, size);
	GlobalUnlock(hglobal);
	GlobalFree(hglobal);
	DeleteEnhMetaFile(hEmf);
	
		
	// Save text objects for job-info realization and printing

	// write text records into archive
	pos = m_objects.GetHeadPosition();
	while (pos != NULL)
		{
		CDrawText* pObj = (CDrawText*)(m_objects.GetNext(pos));
		LOGFONT *plf;
		if ((plf=pObj->GetLogFontCopy()) != NULL)	// is text object
			{
			TEXTBOX tbox;
			tbox.position = pObj->m_position;
			tbox.color = pObj->m_color;
			tbox.align = pObj->m_align;
			tbox.lf = pObj->m_lf;
			strncpy(tbox.text,pObj->m_text,SEPMAXTEXT);
			ar.Write(&tbox,sizeof(TEXTBOX));
			} 
		}
	return TRUE;
}		