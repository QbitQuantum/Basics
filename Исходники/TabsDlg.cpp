void CTabsDlg::DockWindow(int ID , bool dock)
{
	DockedWindowInfo *info = NULL;
	m_Windows.Lookup((WORD)ID , (void* &)info);

	ASSERT(info);
	ASSERT(m_Tabs.GetSafeHwnd());

	ShowAllWindows(FALSE);

	if (!dock) {
		//make a containing window and assign the dialog to it
		CRect rect;
		CString classname = AfxRegisterWndClass(CS_DBLCLKS , 0 , 0 , 0);
		info->m_State = DockedWindowInfo::FLOATING;

		info->m_Window->GetWindowRect(rect);
		info->m_Container.CreateEx(WS_EX_TOOLWINDOW , classname , info->m_Title , WS_THICKFRAME | WS_SYSMENU | WS_POPUP | WS_CAPTION, rect , this , 0);
		info->m_Window->SetParent(&info->m_Container);
		info->m_Window->ShowWindow(TRUE);

		info->m_Container.SetDockManager(this);
		info->m_Container.ShowWindow(TRUE);
		info->m_Container.SetDialog(info->m_Window , info->m_ID);

		if (info->m_TabControlIndex >= 0) {
			m_Tabs.DeleteItem(info->m_TabControlIndex);
		}

		if (m_Tabs.GetItemCount() > 0) {
			m_Tabs.SetCurFocus(0);
		}

		CString placementName = info->m_Title + "Placement";
		LoadWindowPlacement(info->m_Container , placementName);
	} else {
		info->m_State = DockedWindowInfo::DOCKED;

		info->m_TabControlIndex = m_Tabs.InsertItem(TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM , 0 , info->m_Title , info->m_ImageID , (LPARAM)info);

		info->m_Window->SetParent(this);
		info->m_Window->ShowWindow(TRUE);

		info->m_Container.SetDockManager(NULL);	//so it doesn't try to call back and redock this window
		info->m_Container.DestroyWindow();

		CRect rect;
		GetWindowRect(rect);

		//stupid hack to get the window reitself properly
		rect.DeflateRect(0,0,0,1);
		MoveWindow(rect);
		rect.InflateRect(0,0,0,1);
		MoveWindow(rect);
	}

	UpdateTabControlIndices();
	FocusWindow(ID);

	if (info->m_DockCallback) {
		info->m_DockCallback(dock , info->m_ID , info->m_Window);
	}

	SaveWindowPlacement();
}