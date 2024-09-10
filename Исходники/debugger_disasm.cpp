CDisasm::CDisasm(HINSTANCE _hInstance, HWND _hParent, DebugInterface *_cpu) : Dialog((LPCSTR)IDD_DISASM, _hInstance, _hParent)
{
	cpu = _cpu;
	lastTicks = CoreTiming::GetTicks();
	keepStatusBarText = false;

	SetWindowText(m_hDlg, ConvertUTF8ToWString(_cpu->GetName()).c_str());
#ifdef THEMES
	//if (WTL::CTheme::IsThemingSupported())
		//EnableThemeDialogTexture(m_hDlg ,ETDT_ENABLETAB);
#endif
	int x = g_Config.iDisasmWindowX == -1 ? 500 : g_Config.iDisasmWindowX;
	int y = g_Config.iDisasmWindowY == -1 ? 200 : g_Config.iDisasmWindowY;
	int w = g_Config.iDisasmWindowW;
	int h = g_Config.iDisasmWindowH;
	// Start with the initial size so we have the right minimum size from the rc.
	SetWindowPos(m_hDlg, 0, x, y, 0, 0, SWP_NOSIZE);

	CtrlDisAsmView *ptr = CtrlDisAsmView::getFrom(GetDlgItem(m_hDlg,IDC_DISASMVIEW));
	ptr->setDebugger(cpu);
	ptr->gotoAddr(0x00000000);

	CtrlRegisterList *rl = CtrlRegisterList::getFrom(GetDlgItem(m_hDlg,IDC_REGLIST));
	rl->setCPU(cpu);

	GetWindowRect(m_hDlg, &defaultRect);

	//symbolMap.FillSymbolListBox(GetDlgItem(m_hDlg, IDC_FUNCTIONLIST),ST_FUNCTION);
	symbolMap.FillSymbolComboBox(GetDlgItem(m_hDlg, IDC_FUNCTIONLIST),ST_FUNCTION);

	GetWindowRect(GetDlgItem(m_hDlg, IDC_REGLIST), &regRect);
	GetWindowRect(GetDlgItem(m_hDlg, IDC_DISASMVIEW), &disRect);
	GetWindowRect(GetDlgItem(m_hDlg, IDC_BREAKPOINTLIST), &breakpointRect);
	GetWindowRect(GetDlgItem(m_hDlg, IDC_BREAKPOINTLIST), &defaultBreakpointRect);

	HWND tabs = GetDlgItem(m_hDlg, IDC_LEFTTABS);

	TCITEM tcItem;
	ZeroMemory (&tcItem,sizeof (tcItem));
	tcItem.mask			= TCIF_TEXT;
	tcItem.dwState		= 0;
	tcItem.pszText		= L"Regs";
	tcItem.cchTextMax	= (int)wcslen(tcItem.pszText)+1;
	tcItem.iImage		= 0;
	int result1 = TabCtrl_InsertItem(tabs, TabCtrl_GetItemCount(tabs),&tcItem);
	tcItem.pszText		= L"Funcs";
	tcItem.cchTextMax	= (int)wcslen(tcItem.pszText)+1;
	int result2 = TabCtrl_InsertItem(tabs, TabCtrl_GetItemCount(tabs),&tcItem);
	ShowWindow(GetDlgItem(m_hDlg, IDC_REGLIST), SW_NORMAL);
	ShowWindow(GetDlgItem(m_hDlg, IDC_FUNCTIONLIST), SW_HIDE);
	SetTimer(m_hDlg,1,1000,0);
	
	// subclass the goto edit box
	HWND editWnd = GetDlgItem(m_hDlg,IDC_ADDRESS);
	DefGotoEditProc = (WNDPROC)GetWindowLongPtr(editWnd,GWLP_WNDPROC);
	SetWindowLongPtr(editWnd,GWLP_WNDPROC,(LONG_PTR)GotoEditProc); 
	
	// init memory viewer
	CtrlMemView *mem = CtrlMemView::getFrom(GetDlgItem(m_hDlg,IDC_DEBUGMEMVIEW));
	mem->setDebugger(_cpu);
	
	breakpointList = new CtrlBreakpointList(GetDlgItem(m_hDlg,IDC_BREAKPOINTLIST));
	breakpointList->setCpu(cpu);
	breakpointList->setDisasm(ptr);
	breakpointList->reloadBreakpoints();

	threadList = new CtrlThreadList(GetDlgItem(m_hDlg,IDC_THREADLIST));
	threadList->reloadThreads();

	stackTraceView = new CtrlStackTraceView(GetDlgItem(m_hDlg,IDC_STACKFRAMES));
	stackTraceView->setCpu(cpu);
	stackTraceView->setDisasm(ptr);
	stackTraceView->loadStackTrace();
	
	// init bottom "tab"
	changeSubWindow(SUBWIN_FIRST);

	// init status bar
	statusBarWnd = CreateStatusWindow(WS_CHILD | WS_VISIBLE, L"", m_hDlg, IDC_DISASMSTATUSBAR);
	if (g_Config.bDisplayStatusBar == false)
	{
		ShowWindow(statusBarWnd,SW_HIDE);
	}

	// Actually resize the window to the proper size (after the above setup.)
	if (w != -1 && h != -1)
	{
		// this will also call UpdateSize
		SetWindowPos(m_hDlg, 0, x, y, w, h, 0);
	}

	SetDebugMode(true, true);
}