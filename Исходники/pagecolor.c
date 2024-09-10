/*------------------------------------------------
  Initialize
--------------------------------------------------*/
void OnInit(HWND hDlg)
{
	ColorBox colors[2];
	HWND quality_cb = GetDlgItem(hDlg, IDC_FONTQUAL);
	HDC hdc;
	LOGFONT logfont;
	HFONT hfont;
	m_transition=-1; // start transition lock
	// setting of "background" and "text"
	colors[0].hwnd = GetDlgItem(hDlg, IDC_COLFORE);
	colors[0].color = api.GetInt(L"Clock",L"ForeColor",TCOLOR(TCOLOR_DEFAULT));
	colors[1].hwnd = GetDlgItem(hDlg, IDC_COLBACK);
	colors[1].color = api.GetInt(L"Clock",L"BackColor",TCOLOR(TCOLOR_DEFAULT));
	ColorBox_Setup(colors, 2);
	
	// if color depth is 256 or less
	hdc = CreateICA("DISPLAY", NULL, NULL, NULL);
	if(GetDeviceCaps(hdc, BITSPIXEL) <= 8) {
		EnableDlgItem(hDlg, IDC_COLFORE_BTN, FALSE);
		EnableDlgItem(hDlg, IDC_COLBACK_BTN, FALSE);
	}
	DeleteDC(hdc);
	
	InitComboFont(hDlg);
	
	SetComboFontSize(hDlg, TRUE);
	
	
	CheckDlgButton(hDlg, IDC_BOLD, api.GetInt(L"Clock", L"Bold", 0));
	CheckDlgButton(hDlg, IDC_ITALIC, api.GetInt(L"Clock", L"Italic", 0));
	
	hfont = (HFONT)SendMessage(hDlg, WM_GETFONT, 0, 0);
	GetObject(hfont, sizeof(LOGFONT), &logfont);
	logfont.lfWeight = FW_BOLD;
	hfont = CreateFontIndirect(&logfont);
	SendDlgItemMessage(hDlg, IDC_BOLD, WM_SETFONT, (WPARAM)hfont, 0);
	
	logfont.lfWeight = FW_NORMAL;
	logfont.lfItalic = 1;
	hfont = CreateFontIndirect(&logfont);
	SendDlgItemMessage(hDlg, IDC_ITALIC, WM_SETFONT, (WPARAM)hfont, 0);
	
	SendDlgItemMessage(hDlg, IDC_SPINCHEIGHT, UDM_SETRANGE32, (WPARAM)-999,999);
	SendDlgItemMessage(hDlg, IDC_SPINCHEIGHT, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"ClockHeight", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINCWIDTH, UDM_SETRANGE32, (WPARAM)-999,999);
	SendDlgItemMessage(hDlg, IDC_SPINCWIDTH, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"ClockWidth", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINLHEIGHT, UDM_SETRANGE32, (WPARAM)-64,64);
	SendDlgItemMessage(hDlg, IDC_SPINLHEIGHT, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"LineHeight", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINVPOS, UDM_SETRANGE32, (WPARAM)-200,200);
	SendDlgItemMessage(hDlg, IDC_SPINVPOS, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"VertPos", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINHPOS, UDM_SETRANGE32, (WPARAM)-200,200);
	SendDlgItemMessage(hDlg, IDC_SPINHPOS, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"HorizPos", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINANGLE, UDM_SETRANGE32, (WPARAM)-360,360);
	SendDlgItemMessage(hDlg, IDC_SPINANGLE, UDM_SETPOS32, 0, api.GetInt(L"Clock", L"Angle", 0));
	
	SendDlgItemMessage(hDlg, IDC_SPINALPHA, UDM_SETRANGE32, 0,100);
	SendDlgItemMessage(hDlg, IDC_SPINALPHA, UDM_SETPOS32, 0, api.GetInt(L"Taskbar", L"AlphaTaskbar", 0));
	
	ComboBox_AddString(quality_cb, L"Default");            // 0 = DEFAULT_QUALITY
	ComboBox_AddString(quality_cb, L"Draft");              // 1 = DRAFT_QUALITY
	ComboBox_AddString(quality_cb, L"Proof");              // 2 = PROOF_QUALITY
	ComboBox_AddString(quality_cb, L"NonAntiAliased");     // 3 = NONANTIALIASED_QUALITY
	ComboBox_AddString(quality_cb, L"AntiAliased (Win7)"); // 4 = ANTIALIASED_QUALITY
	ComboBox_AddString(quality_cb, L"ClearType (WinXP+)"); // 5 = CLEARTYPE_QUALITY
	ComboBox_AddString(quality_cb, L"ClearType Natural");  // 6 = CLEARTYPE_NATURAL_QUALITY
	ComboBox_SetCurSel(quality_cb,api.GetInt(L"Clock",L"FontQuality",CLEARTYPE_QUALITY));
	m_transition=0; // end transition lock, ready to go
}