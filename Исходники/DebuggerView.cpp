void CDebuggerView::OnInitialUpdate()
{
    cdxCDynamicFormView::OnInitialUpdate();

    static bool firstTime = true;

    if (firstTime)
    {
        theApp.GetMainFrame()->Init();
        CWnd* tempWnd = GetDlgItem(IDC_DB_EDITOR);
        CRect editorRect;
        tempWnd->GetWindowRect(editorRect);

        CRect dialogRect;
        GetClientRect(dialogRect);
        ClientToScreen(dialogRect);

        editorRect.OffsetRect(-dialogRect.TopLeft());

        m_editor.Create(GetSafeHwnd(), editorRect);

//jj		m_localsGrid.CreateGrid(this, IDC_DB_LOCALS);
//jj		m_localsGrid.Init();
//jj		m_watchGrid.CreateGrid(this, IDC_DB_WATCH);
//jj		m_watchGrid.Init();
//jj		m_watchGrid.BuildWatch("Locals");

///////////		theApp.GetMainFrame()->GetWatchBar().GetGrid().BuildWatch("Locals");

//jj		AddSzControl(m_localsGrid, 100, 0, 100, 50);
//jj		AddSzControl(m_watchGrid, 100, 50, 100, 100);
//jj		AddSzControl(IDC_DB_LOCALSSTATIC, 100, 0, 100, 0);
//jj		AddSzControl(IDC_DB_WATCHSTATIC, 100, 50, 100, 50);
//		AddSzControl(m_actionList, 0, 0, 0, 50);
//		AddSzControl(m_generatedActionList, 0, 50, 0, 100);
        AddSzControl(m_editor.GetWindowHandle(), mdResize, mdResize);
//		AddSzControl(m_actionGrid->GetSafeHwnd(), mdResize, mdResize);

//		m_actionList.SetExtendedStyle(m_actionList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
//		m_actionList.InsertColumn(0, "Actions", LVCFMT_LEFT, 200);
//		m_generatedActionList.SetExtendedStyle(m_generatedActionList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
//		m_generatedActionList.InsertColumn(0, "Generated Actions", LVCFMT_LEFT, 200);

        firstTime = false;

//		m_gridActive = true;
//		::ShowWindow(m_editor.GetWindowHandle(), SW_HIDE);

        tempWnd->DestroyWindow();

        m_editor.SendEditor(SCI_SETFOCUS, 1);
    }
}