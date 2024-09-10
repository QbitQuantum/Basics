/*----------------------------------------------------------------------------------------------
	The hwnd has been attached.
----------------------------------------------------------------------------------------------*/
void HwMainWnd::PostAttach(void)
{
	StrAppBuf strbT; // Holds temp string

	// Set the default caption text.
	strbT.Load(kstidHelloWorld);
	::SendMessage(m_hwnd, WM_SETTEXT, 0, (LPARAM)strbT.Chars());

	// This creates the main frame window and sets it as the current window. It also
	// creates the rebar and status bar.
	SuperClass::PostAttach();

	const int rgrid[] =
	{
		kridTBarStd,
		kridHwTBarIns,
		kridHwTBarTools,
		kridHwTBarWnd,
	};

	GetMenuMgr()->LoadToolBars(rgrid, SizeOfArray(rgrid));

	// Create the menu bar.
	AfMenuBarPtr qmnbr;
	qmnbr.Create();
	qmnbr->Initialize(m_hwnd, kridAppMenu, kridAppMenu, "Menu Bar");
	m_vqtlbr.Push(qmnbr.Ptr());

	// Create the toolbars.
	AfToolBarPtr qtlbr;

	qtlbr.Create();
	qtlbr->Initialize(kridTBarStd, kridTBarStd, "Standard");
	m_vqtlbr.Push(qtlbr);

	qtlbr.Create();
	qtlbr->Initialize(kridHwTBarIns, kridHwTBarIns, "Insert");
	m_vqtlbr.Push(qtlbr);

	qtlbr.Create();
	qtlbr->Initialize(kridHwTBarTools, kridHwTBarTools, "Tools");
	m_vqtlbr.Push(qtlbr);

	qtlbr.Create();
	qtlbr->Initialize(kridHwTBarWnd, kridHwTBarWnd, "Window");
	m_vqtlbr.Push(qtlbr);

	// Load window settings.
	LoadSettings(NULL, false);

	g_app.AddCmdHandler(this, 1);
	m_qstbr->RestoreStatusText();

	// Create the client window.
	const int kwidChild = 1000;
	WndCreateStruct wcs;
	wcs.InitChild("STATIC", m_hwnd, kwidChild);
	m_qwndHost.Create();
	m_qwndHost->CreateAndSubclassHwnd(wcs);

	Assert(memcmp(&CLSID_SaCtrlEvent, &DIID__DSAEvents, isizeof(GUID)) == 0);

	CComCoClass<SaCtrlEvent>::CreateInstance(&m_qsce);
	IUnknownPtr qunk;
	CheckHr(AtlAxCreateControlEx(L"SA.SACtrl.1", m_qwndHost->Hwnd(), NULL, NULL, &qunk,
		DIID__DSAEvents, (IUnknown *)m_qsce.Ptr()));
	CheckHr(qunk->QueryInterface(DIID__DSA, (void **)&m_qctrl));
	m_qsce->Init(this, m_qctrl);
	StrUni stu(L"baluchi.wav");
	CheckHr(m_qctrl->put_WaveFile(stu.Bstr()));
	CheckHr(m_qctrl->raw_SetGraphs(GRAPH_MAGNITUDE, GRAPH_MAGNITUDE));
	CheckHr(m_qctrl->put_ShowContextMenu(false));
	CheckHr(m_qctrl->put_ShowCursorContextMenu(false));

	::ShowWindow(m_qwndHost->Hwnd(), SW_SHOW);

	g_app.AddCmdHandler(this, 1);
}