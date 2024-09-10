void SppLog::LogAudioUnit(int Code, int source, int Severity, LPVOID Data)
{
		if (!m_hLogDlg)
		return;

	// Initialize
	LRESULT lr;
	HWND hEdit=NULL;
	WCHAR prefix[6], prtcode[20], src[20];
	GETTEXTLENGTHEX tl;
	CHARFORMAT cf;
	tl.codepage =  CP_ACP;
	tl.flags = GTL_DEFAULT;
	hEdit = GetDlgItem(m_hLogDlg, IDC_EDIT_LOG);
	SendMessage(hEdit,EM_SHOWSCROLLBAR    , (WPARAM)SB_VERT, TRUE);

	// Severity to colour and Prefix
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;
	switch (Severity)
	{
	case ERR:
		cf.crTextColor = RGB(180,0,0);
		wmemcpy(prefix,L"[E] ",5);
		break;
	case FATAL:
		cf.crTextColor = RGB(250,0,0);
		wmemcpy(prefix,L"[F] ",5);
		break;
	case WARN:
		cf.crTextColor = RGB(255,140,0);
		wmemcpy(prefix,L"[W] ",5);
		break;
	default:
		cf.dwEffects = CFE_AUTOCOLOR;
		wmemcpy(prefix,L"[I] ",5);
	}

	switch (source)
	{
	case WMSPP_LOG_CNTRL:
		wmemcpy(src,L"<Cntrl ",sizeof(L"<Cntrl ")/sizeof(TCHAR));
		break;
	case WMSPP_LOG_AUDIO:
		wmemcpy(src,L"<Audio ",sizeof(L"<Audio ")/sizeof(TCHAR));
		break;
	case WMSPP_LOG_PRSC:
		wmemcpy(src,L"<Prcss ",sizeof(L"<Prcss ")/sizeof(TCHAR));
		break;
	default:
		wmemcpy(src,L"<????? ",sizeof(L"<????? ")/sizeof(TCHAR));
	}


	SendMessage(hEdit,EM_SETCHARFORMAT, (WPARAM)SCF_SELECTION, (LPARAM)&cf);

	// Print one Line

	// Prefix
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	SendMessage(hEdit,EM_SETSEL    , lr, lr);
	SendMessage(hEdit,EM_REPLACESEL     , TRUE, (LPARAM)prefix);
	// Source
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	SendMessage(hEdit,EM_SETSEL    , lr, lr);
	SendMessage(hEdit,EM_REPLACESEL     , TRUE, (LPARAM)src);
	// Code
	swprintf_s(prtcode, 10,L"%d>: ", Code);
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	SendMessage(hEdit,EM_SETSEL    , lr, lr);
	SendMessage(hEdit,EM_REPLACESEL     , TRUE, (LPARAM)prtcode);
	// Data
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	SendMessage(hEdit,EM_SETSEL    , lr, lr);
	SendMessage(hEdit,EM_REPLACESEL     , TRUE, (LPARAM)(LPCWSTR)Data);
	// New line
	lr = SendMessage(hEdit,EM_GETTEXTLENGTHEX   , (WPARAM)&tl,0);
	SendMessage(hEdit,EM_SETSEL    , lr, lr);
	SendMessage(hEdit,EM_REPLACESEL     , TRUE, (LPARAM)L"\r\n");

	// Scroll to bottom
	SendMessage(hEdit,EM_SCROLLCARET       , 0, 0);
}