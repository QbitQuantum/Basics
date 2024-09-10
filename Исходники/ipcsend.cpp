void CSendCombo::DrawItem( LPDRAWITEMSTRUCT lpDIS )
{
	if( !lpDIS->itemData )
		return;

	// get dc to draw on
	CDC* pDC = CDC::FromHandle( lpDIS->hDC );
	if( pDC == NULL )
		return;
	// create background for default
	COLORREF crBackground = GetSysColor(COLOR_WINDOW);
	// get CPlayer at this index
	CPlayer *pPlayer = (CPlayer *)GetItemDataPtr(lpDIS->itemID);
	if( pPlayer == NULL ||
		(int)pPlayer == -1 )
		return;

	CString sName;
	sName = pPlayer->GetName();
			
	BOOL bRet = FALSE;
	CBitmap workBM;
	CDC workDC;
	workDC.CreateCompatibleDC( pDC );

	// this player has been selected
	if( m_iSelect[lpDIS->itemID] )
	{
		bRet = workBM.LoadBitmap(IDB_PLYR_SELECTED);
	}
	else
	{
		bRet = workBM.LoadBitmap(IDB_NO_SELECT);
	}
	if( !bRet )
		return;

	CBitmap *pOldWork = workDC.SelectObject( &workBM );

	DWORD dwOldText;
	int iOldMode;
	COLORREF crOldBackColor;

	int iX = lpDIS->rcItem.left + 1;
	int iY = lpDIS->rcItem.top + 1;

	// draw whole listbox item, normal
	if( lpDIS->itemAction & ODA_DRAWENTIRE )
	{
		// COLOR_WINDOW
		CBrush br( crBackground );
		pDC->FillRect( &lpDIS->rcItem, &br );
		crOldBackColor = pDC->SetBkColor( crBackground );
		ASSERT( crOldBackColor != 0x80000000 );

		// COLOR_WINDOWTEXT
		dwOldText = pDC->SetTextColor( 
			GetSysColor(COLOR_WINDOWTEXT) );
		iOldMode = pDC->SetBkMode( TRANSPARENT );

		pDC->BitBlt( iX, iY, IPC_MSG_BM_HEIGHT, IPC_MSG_BM_HEIGHT,
			&workDC, 0, 0, SRCCOPY );

		iX += IPC_MSG_BM_HEIGHT;
		pDC->TextOut( iX, iY, sName, sName.GetLength() );

		pDC->SetBkColor( crOldBackColor );
		pDC->SetTextColor( dwOldText );
		pDC->SetBkMode( iOldMode );
	}
	iX = lpDIS->rcItem.left + 1;

	// item has been selected, draw highlighted
	if( (lpDIS->itemState & ODS_SELECTED) &&
	    (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush br( GetSysColor(COLOR_HIGHLIGHT) );
		pDC->FillRect( &lpDIS->rcItem, &br );

		dwOldText = pDC->SetTextColor( 
			GetSysColor(COLOR_HIGHLIGHTTEXT) );
		iOldMode = pDC->SetBkMode( TRANSPARENT );

		pDC->BitBlt( iX, iY, IPC_MSG_BM_HEIGHT, IPC_MSG_BM_HEIGHT,
			&workDC, 0, 0, SRCCOPY );

		iX += IPC_MSG_BM_HEIGHT;
		pDC->TextOut( iX, iY, sName, sName.GetLength() );

		pDC->SetBkColor( crOldBackColor );
		pDC->SetTextColor( dwOldText );
		pDC->SetBkMode( iOldMode );
	}
	iX = lpDIS->rcItem.left + 1;

	// item has been de-selected, remove highlight
	if( !(lpDIS->itemState & ODS_SELECTED) &&
	    (lpDIS->itemAction & ODA_SELECT) )
	{
		CBrush br( crBackground );
		pDC->FillRect( &lpDIS->rcItem, &br );

		dwOldText = pDC->SetTextColor( 
			GetSysColor(COLOR_WINDOWTEXT) );
		iOldMode = pDC->SetBkMode( TRANSPARENT );

		pDC->BitBlt( iX, iY, IPC_MSG_BM_HEIGHT, IPC_MSG_BM_HEIGHT,
			&workDC, 0, 0, SRCCOPY );

		iX += IPC_MSG_BM_HEIGHT;
		pDC->TextOut( iX, iY, sName, sName.GetLength() );

		pDC->SetBkColor( crOldBackColor );
		pDC->SetTextColor( dwOldText );
		pDC->SetBkMode( iOldMode );
	}

	sName.Empty();
	workDC.SelectObject( pOldWork );
	workDC.DeleteDC();
	workBM.DeleteObject();
}