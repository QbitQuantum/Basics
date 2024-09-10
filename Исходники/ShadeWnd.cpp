BOOL CShadeWnd::CreateShadow(HDC hdc,CSize szWindow,CRect rcMargin)
{
	HDC hdcMask = ::CreateCompatibleDC(hdc);
	HBITMAP	hBmpMask = ::CreateCompatibleBitmap( hdc, szWindow.cx,szWindow.cy );
	HGDIOBJ hBmpOldMask = ( HBITMAP )::SelectObject( hdcMask, hBmpMask );

	if(hdcMask && hBmpMask)
	{
		CRect rcClip(rcMargin.left,rcMargin.top,szWindow.cx - rcMargin.right,szWindow.cy - rcMargin.bottom);

		int nSave = SaveDC(hdc);
		HRGN hRgn = ::CreateRectRgnIndirect( &rcClip );
		::ExtSelectClipRgn( hdc, hRgn ,RGN_DIFF);
		::DeleteObject(hRgn);
		HBRUSH hbrush = CreateSolidBrush(RGB(0,0,0));
		FillRect(hdc,CRect(0,0,szWindow.cx,szWindow.cy),hbrush);
		DeleteObject(hbrush);
		RestoreDC( hdc,nSave );

		//½«ÒõÓ°Í¼Æ¬»æÖÆµ½hdcMask
		m_pMask->Draw(hdcMask,CRect(0,0,szWindow.cx,szWindow.cy));

		BLENDFUNCTION bf = {AC_SRC_OVER,0,255,AC_SRC_ALPHA};
		::AlphaBlend(hdc,0,0,szWindow.cx,szWindow.cy,hdcMask,0,0,szWindow.cx,szWindow.cy,bf);

		::SelectObject( hdcMask, hBmpOldMask );
		::DeleteObject( hBmpMask );
		::DeleteDC( hdcMask );

		return TRUE;
	}
	return FALSE;
}