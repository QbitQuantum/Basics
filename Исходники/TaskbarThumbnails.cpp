LRESULT CALLBACK Explorerplusplus::MainWndTaskbarThumbnailProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(uMsg == m_uTaskbarButtonCreatedMessage)
	{
		if(m_pTaskbarList != NULL)
		{
			m_pTaskbarList->Release();
		}

		CoCreateInstance(CLSID_TaskbarList,NULL,CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pTaskbarList));
		m_pTaskbarList->HrInit();

		m_bTaskbarInitialised = TRUE;

		/* Add each of the jump list tasks. */
		SetupJumplistTasks();

		/* Register each of the tabs. */
		for(auto itr = m_TabProxyList.begin();itr != m_TabProxyList.end();itr++)
		{
			BOOL bActive = (itr->iTabId == m_iObjectIndex);

			RegisterTab(itr->hProxy,EMPTY_STRING,bActive);
			HandleTabText(itr->iTabId);
			SetTabIcon(itr->iTabId);
		}

		RemoveWindowSubclass(hwnd,MainWndProcStub,0);

		return 0;
	}

	return DefSubclassProc(hwnd,uMsg,wParam,lParam);
}