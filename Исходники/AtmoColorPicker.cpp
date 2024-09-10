ATMO_BOOL CAtmoColorPicker::InitDialog(WPARAM wParam) 
{
	CLanguage *Lng = new CLanguage;

	HWND hwndCtrl;
	hwndCtrl = this->getDlgItem(IDC_EDT_RED);
	Edit_LimitText(hwndCtrl,3);
	hwndCtrl = this->getDlgItem(IDC_EDT_GREEN);
	Edit_LimitText(hwndCtrl,3);
	hwndCtrl = this->getDlgItem(IDC_EDT_BLUE);
	Edit_LimitText(hwndCtrl,3);

	hwndCtrl = this->getDlgItem(IDC_SL_RED);
	SendMessage(hwndCtrl, TBM_SETRANGEMIN, 0, 0);
	SendMessage(hwndCtrl, TBM_SETRANGEMAX, 0, 255);
	SendMessage(hwndCtrl, TBM_SETPOS, 1, this->m_iRed);
	SendMessage(hwndCtrl, TBM_SETTICFREQ, 8, 0);

	hwndCtrl = this->getDlgItem(IDC_SL_GREEN);
	SendMessage(hwndCtrl, TBM_SETRANGEMIN, 0, 0);
	SendMessage(hwndCtrl, TBM_SETRANGEMAX, 0, 255);
	SendMessage(hwndCtrl, TBM_SETPOS, 1, this->m_iGreen);
	SendMessage(hwndCtrl, TBM_SETTICFREQ, 8, 0);

	hwndCtrl = this->getDlgItem(IDC_SL_BLUE);
	SendMessage(hwndCtrl, TBM_SETRANGEMIN, 0, 0);
	SendMessage(hwndCtrl, TBM_SETRANGEMAX, 0, 255);
	SendMessage(hwndCtrl, TBM_SETPOS, 1, this->m_iBlue);
	SendMessage(hwndCtrl, TBM_SETTICFREQ, 8, 0);

	UpdateColorControls(ATMO_TRUE, ATMO_TRUE);

	Lng->szCurrentDir[Lng->SetLngPath()];

	sprintf(Lng->szFileINI, "%s\\Language.ini\0", Lng->szCurrentDir);

	GetPrivateProfileString("Common", "Language", "English", Lng->szLang, 256, Lng->szFileINI);

	// Read Buffer from IniFile
	sprintf(Lng->szTemp, "%s\\%s.xml\0", Lng->szCurrentDir, Lng->szLang);

	Lng->XMLParse(Lng->szTemp, Lng->sTextCPicker, "ColorPicker");

	SendMessage(getDlgItem(IDC_STATIC22), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sTextCPicker[0]));
	SendMessage(getDlgItem(IDC_STATIC23), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sTextCPicker[1]));
	SendMessage(getDlgItem(IDC_STATIC24), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sTextCPicker[2]));
	SendMessage(this->m_hDialog, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sTextCPicker[3]));
	SendMessage(getDlgItem(IDCANCEL), WM_SETTEXT, 0, (LPARAM)(LPCTSTR)(Lng->sTextCPicker[4]));

	return ATMO_TRUE;

}