	void make_child()
	{
		//HWND wnd_destroy = child;
		if (m_wnd_child)
		{
			ShowWindow(m_wnd_child, SW_HIDE);
			DestroyWindow(m_wnd_child);
			m_wnd_child=NULL;
		}

		HWND wnd_tab = GetDlgItem(m_wnd, IDC_TAB1);
		
		RECT tab;
		
		GetWindowRect(wnd_tab,&tab);
		MapWindowPoints(HWND_DESKTOP, m_wnd, (LPPOINT)&tab, 2);
		
		TabCtrl_AdjustRect(wnd_tab,FALSE,&tab);
		
		unsigned count = tabsize(g_tabs_appearance);
		if (cfg_child_appearance >= count) cfg_child_appearance = 0;

		if (cfg_child_appearance < count && cfg_child_appearance >= 0)
		{
			m_wnd_child = g_tabs_appearance[cfg_child_appearance]->create(m_wnd);
		}

		//SetWindowPos(child,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
		if (m_wnd_child) 
		{
			EnableThemeDialogTexture(m_wnd_child, ETDT_ENABLETAB);
		}

		SetWindowPos(m_wnd_child, 0, tab.left, tab.top, tab.right-tab.left, tab.bottom-tab.top, SWP_NOZORDER);
		SetWindowPos(wnd_tab,HWND_BOTTOM,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
		
		ShowWindow(m_wnd_child, SW_SHOWNORMAL);
		//UpdateWindow(child);
	}