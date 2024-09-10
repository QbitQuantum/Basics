LRESULT COXAutoComplete::KeyboardProc(int code,
				WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_pThis);

	if (code<0)
		return ::CallNextHookEx(m_pThis->m_hkKbrd,code,wParam,lParam);
	else
	{
		CString sText;
		CWnd* pWnd=CWnd::GetFocus();
		COXAutoStorage* pStorage;
		_AFX_THREAD_STATE* pThreadState=AfxGetThreadState();
		if(pThreadState->m_hTrackingWindow==NULL && pWnd!=NULL && 
			m_pThis->m_mpStorage.Lookup(pWnd->m_hWnd,pStorage))
		{
			if (lParam<0)//key is pressed
			{
				switch (wParam)
				{
				case VK_NEXT:
				case VK_PRIOR:
				case VK_UP:
				case VK_DOWN:
					m_pThis->ChangeSel(PtrToInt(wParam));
					return TRUE;
					break;
				default:
					if (wParam>VK_HELP)
					{
						pWnd->GetWindowText(sText);
						m_pThis->OnContentsChange(pWnd->m_hWnd,sText);
					}

				}
			}
			else
			{
				switch (wParam)
				{
					case VK_NEXT:
					case VK_PRIOR:
					case VK_UP:
					case VK_DOWN:
						return TRUE;
				}
			}
		}
	}
	return ::CallNextHookEx(m_pThis->m_hkKbrd,code,wParam,lParam);
}