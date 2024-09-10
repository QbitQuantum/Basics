/*------------------------------------------------
  initialize
--------------------------------------------------*/
void OnInit(HWND hDlg)
{
	PMOUSESTRUCT pitem;
	RECT rc;
	BOOL b;
	
	m_bInit = FALSE;
	
	if(GetMyRegLong(m_section, "ver031031", 0) == 0)
	{
		SetMyRegLong(m_section, "ver031031", 1);
		ImportOldMouseFunc(); // common/mousestruct.c
	}
	
	// common/mousestruct.c
	m_pMouseCommand = LoadMouseFunc();
	
	// common/tclang.c
	SetDialogLanguage(hDlg, "Mouse", g_hfontDialog);
	
	GetWindowRect(GetDlgItem(hDlg, IDC_MOUSEOPT), &rc);
	m_widthOpt = rc.right - rc.left;
	
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_LEFTBUTTON, "LButton"));
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_RIGHTBUTTONM, "RButton"));
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_MIDDLEBUTTONM, "MButton"));
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_XBUTTON1, "XButton1"));
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_XBUTTON2, "XButton2"));
#if TC_ENABLE_WHEEL
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_WHEELUP, "WheelUp"));
	CBAddString(hDlg, IDC_MOUSEBUTTON,
		(LPARAM)MyString(IDS_WHEELDOWN, "WheelDown"));
#endif
	
	InitFunction(hDlg, IDC_MOUSEFUNC);
	
	pitem = m_pMouseCommand;
	while(pitem)
	{
		CBAddString(hDlg, IDC_NAMECLICK, (LPARAM)pitem->name);
		pitem = pitem->next;
	}
	
	m_nCurrent = -1;
	CBSetCurSel(hDlg, IDC_NAMECLICK, 0);
	OnName(hDlg);
	
	CheckDlgButton(hDlg, IDC_LMOUSEPASSTHRU,
		GetMyRegLong(m_section, "LeftMousePassThrough",
			(g_winver&WIN10RS1) != 0));
	
	b = GetMyRegLong(NULL, "RightClickMenu", TRUE);
	b = GetMyRegLong(m_section, "RightClickMenu", b);
	CheckDlgButton(hDlg, IDC_RCLICKMENU, b);
	
	m_bInit = TRUE;
}