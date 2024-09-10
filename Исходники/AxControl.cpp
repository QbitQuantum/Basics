void CAxControl::OnShowWindow(BOOL bShowing, int nReason)
{
	if(bShowing == TRUE)
	{
		if(m_time == 0)
			if(m_url != L"")
			{
				CComVariant var;
				m_time = 1;
				m_pCore->m_pWebBrowser2->Navigate((BSTR)m_url.c_str(), &var, &var, &var, &var);
			}

		LONG style = ::GetWindowLongW(m_hWnd, GWL_STYLE);
		if((style & WS_VISIBLE) ==  WS_VISIBLE)
		{
			HWND TChild, MChild, BChild;
			TChild = FindWindowExW(m_hWnd , NULL, L"Shell Embedding", NULL);
			if(TChild != NULL)
			{
				MChild = FindWindowExW(TChild, NULL, L"Shell DocObject View", NULL);
				if(MChild != NULL)
				{
					BChild = FindWindowExW(MChild, NULL, L"Internet Explorer_Server", NULL);
					if(BChild != NULL)
					{
						::SetFocus(BChild);
					}
				}
			}
		}
	}
}