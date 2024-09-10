void CUniKeyMenu::reload()
{
	if (m_pPref->m_vietGUI) {
#ifndef _UNICODE
		initMenu(m_hInst, m_hParentWnd, IDR_KEY_MENU, VnMenuText);
#else
		wchar_t * WVnMenuText[sizeof(VnMenuText)/sizeof(char *)];
		int items = sizeof(VnMenuText)/sizeof(char *);
		int i, maxOutLen, inLen;
		for (i=0; i<items; i++) {
			inLen = -1;
			WVnMenuText[i] = new wchar_t[40];
			maxOutLen = 80;
			VnConvert(CONV_CHARSET_TCVN3, CONV_CHARSET_UNICODE, 
					 (BYTE *)VnMenuText[i], (BYTE *)WVnMenuText[i],
					 inLen, maxOutLen);
		}
		initMenu(m_hInst, m_hParentWnd, IDR_KEY_MENU, WVnMenuText);
		for (i=0; i<items; i++)
			delete [] WVnMenuText[i];
#endif
		setFont(VIET_FONT_NAME, VIET_MENU_FONT_SIZE);
	}
	else {
		initMenu(m_hInst, m_hParentWnd, IDR_KEY_MENU); // Use menu text from the resource
		setFont(_T(""), 0); // use Windows standard font
	}
	SetMenuDefaultItem(m_hMenu, ID_KEY_PANEL, FALSE);
	setMenuItemText(CharsetTable[m_pPref->m_otherCharset].name, ID_KEY_OTHER, FALSE);
	m_charsetItemID = 0;
	selectCharsetMenu(m_pPref->m_codeTable);
	m_inputMethodItemID = inputMethodToCmd(m_pPref->m_inMethod);
	selectInputMethod(inputMethodToCmd(m_pPref->m_inMethod));
}