void CEDClock::DrawClockBit(BYTE nDigit, int nPos)
{
	CRect rc;
	GetClientRect( &rc );
	
	CClientDC dc( this );
	CBitmap bmBuf, *pbmOld;
	
	CDC dcBuf;
	dcBuf.CreateCompatibleDC( &dc );
	bmBuf.CreateCompatibleBitmap( &dc, rc.Width(), rc.Height() );
	pbmOld = (CBitmap*)dcBuf.SelectObject( &bmBuf );

	dcBuf.BitBlt(rc.left,rc.top,rc.right,rc.bottom,&dc,0,0,SRCCOPY);
//dcBuf.FillSolidRect(0,0,rc.Width(), rc.Height(),RGB(255,255,255));
	
	ImageList_DrawEx( m_pClock, nDigit, dcBuf.GetSafeHdc(), 13*nPos,
		0, 13, 23, CLR_DEFAULT, CLR_DEFAULT, ILD_NORMAL );
	dc.BitBlt( 0, 0, rc.Width(), rc.Height(), &dcBuf, 0, 0, SRCCOPY );
	
	dcBuf.SelectObject( pbmOld );
	dcBuf.DeleteDC();
	bmBuf.DeleteObject();
}