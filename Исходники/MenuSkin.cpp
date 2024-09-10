void CMenuSkin::DrawMenuItemText(CDCHandle dc, UINT uMenuRes, WORD wMenuID, const CString &lpszMenuString, const RECT &rect, CBitmapHandle hBitmap, CBitmapHandle hBitmapMask, bool bEnabled, bool bBold)
{
	if (hBitmap == (HBITMAP)-1 || hBitmap == (HBITMAP)-2)
	{
		int iWidth = m_imgMenuIcon.GetWidth() / 2;
		int iBegin = iWidth * (-(int)(HBITMAP)hBitmap - 1);
		int iY = (rect.bottom - rect.top - ICON_WIDTH) / 2;
		RECT rcDest = { rect.left + iY + 1, rect.top + iY, rect.left + iY + iWidth + 1, rect.top + iY + iWidth };
		RECT rcSrc = { iBegin, 0, iBegin + iWidth, m_imgMenuIcon.GetHeight() };
		m_imgMenuIcon.Draw(dc, rcDest, rcSrc);
	}
	else if ( (hBitmap && ::GetObjectType(hBitmap) == OBJ_BITMAP) || 
              (hBitmapMask && ::GetObjectType(hBitmapMask) == OBJ_BITMAP) )
	{
		ICONINFO ii = { TRUE, 8, 8, hBitmapMask, hBitmap };
		CIcon ico;
		ico.CreateIconIndirect(&ii);

		int iY = (rect.bottom - rect.top - ICON_WIDTH) / 2;
		ico.DrawIconEx(dc, rect.left + iY + 1, rect.top + iY, ICON_WIDTH, ICON_WIDTH);
	}

	CString strMenuText = lpszMenuString;
	int n = strMenuText.Find('\n');
	if (n >= 0)
		strMenuText = strMenuText.Mid(0, n);

	TCHAR szAcc[128] = { 0 };
	n = strMenuText.Find('\t');
	if (n >= 0)
	{
		_tcscpy_s(szAcc, strMenuText.Mid(n + 1));
		strMenuText = strMenuText.Mid(0, n);
	}

	RECT rcText = rect;
	rcText.left += ICON_WIDTH + 6;
	rcText.right -= 5;

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(CSkinProperty::GetColor(bEnabled ? Skin_Property_Menu_Text_Color : Skin_Property_Menu_Disabled_Text_Color));
	dc.SelectFont(bBold ? s()->Common()->GetBoldFont() : s()->Common()->GetDefaultFont());
	dc.DrawText(strMenuText, strMenuText.GetLength(), &rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

	if (szAcc[0])
	{
		dc.SetTextColor(CSkinProperty::GetColor(Skin_Property_Menu_Shortcut_Text_Color));
		dc.SelectFont(s()->Common()->GetMenuAccFont());
		dc.DrawText(szAcc, -1, &rcText, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	}
}