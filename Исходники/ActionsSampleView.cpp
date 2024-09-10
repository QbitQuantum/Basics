void CActionsSampleView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	USES_CONVERSION;

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	
	CString strDefFont = _T("Tahoma");
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD |CFM_ITALIC | CFM_UNDERLINE | CFM_STRIKEOUT | CFM_SIZE |
		CFM_COLOR | CFM_OFFSET | CFM_PROTECTED | CFM_FACE;
	cf.dwEffects = CFE_AUTOCOLOR;
	cf.yHeight = 200; //10pt
	cf.bPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

#if (_RICHEDIT_VER >= 0x0200)
	lstrcpyn(cf.szFaceName, strDefFont, LF_FACESIZE);
#else
	lstrcpynA(cf.szFaceName, T2A((LPTSTR) (LPCTSTR) strDefFont), LF_FACESIZE);
#endif

	GetRichEditCtrl().SetDefaultCharFormat(cf);

}