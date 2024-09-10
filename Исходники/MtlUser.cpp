// __nID == 0 then separator
HWND MtlCreateSimpleToolBarCtrl(
		HWND		hWndParent,
		int *		__firstID,
		int *		__lastID,
		UINT		nImageBmpID,
		UINT		nHotImageBmpID,
		int 		cx,
		int 		cy,
		COLORREF	clrMask,
		UINT		nFlags,
		DWORD		dwStyle,
		UINT		nID)
{
	int 	nCount	= int (__lastID - __firstID);
	if (nCount == 0)
		return NULL;

	CImageList	 imgs;
	MTLVERIFY( imgs.Create(cx, cy, nFlags | ILC_MASK, nCount, 1) );

	CBitmap 	 bmp;
	MTLVERIFY( bmp.LoadBitmap(nImageBmpID) );
	imgs.Add(bmp, clrMask);

	CImageList	 imgsHot;
	MTLVERIFY( imgsHot.Create(cx, cy, nFlags | ILC_MASK, nCount, 1) );

	CBitmap 	 bmpHot;
	MTLVERIFY( bmpHot.LoadBitmap(nHotImageBmpID) );
	imgsHot.Add(bmpHot, clrMask);

	TBBUTTON *	 pTBBtn  = (TBBUTTON *) _alloca( nCount * sizeof (TBBUTTON) );

	int 		 nBmp	 = 0;
	int 		 j		 = 0;

	for (; __firstID < __lastID; ++__firstID) {
		ATLASSERT(j < nCount);

		if (*__firstID != 0) {
			pTBBtn[j].iBitmap	= nBmp++;
			pTBBtn[j].idCommand = *__firstID;
			pTBBtn[j].fsState	= TBSTATE_ENABLED;
			pTBBtn[j].fsStyle	= TBSTYLE_BUTTON;
			pTBBtn[j].dwData	= 0;
			pTBBtn[j].iString	= 0;
		} else {
			pTBBtn[j].iBitmap	= 8;
			pTBBtn[j].idCommand = 0;
			pTBBtn[j].fsState	= 0;
			pTBBtn[j].fsStyle	= TBSTYLE_SEP;
			pTBBtn[j].dwData	= 0;
			pTBBtn[j].iString	= 0;
		}

		++j;
	}

	CToolBarCtrl toolbar = ::CreateWindowEx(
									0,
									TOOLBARCLASSNAME,
									NULL,
									dwStyle,
									0,
									0,
									100,
									100,
									hWndParent,
									(HMENU) LongToHandle(nID),
									_Module.GetModuleInstance(),
									NULL);

	toolbar.SetButtonStructSize( sizeof (TBBUTTON) );
	toolbar.AddButtons(nCount, pTBBtn);
	toolbar.SetImageList(imgs);
	toolbar.SetHotImageList(imgsHot);

	return toolbar.m_hWnd;
}