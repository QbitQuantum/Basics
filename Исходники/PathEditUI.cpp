void CPathEditUI::ShowEditWnd()
{
	if (m_pWindow == NULL)
	{
		m_pWindow = new CPathEditWnd();
		ASSERT(m_pWindow);
		m_pWindow->Init(this);

		TCHAR text[MAX_PATH] = {0};
		GetWindowText(m_pWindow->GetHWND(), text, MAX_PATH);

		LPTSTR lpt = StrRChr(text, NULL, _T('.'));

		if (lpt != NULL)
		{
			int nSize = lpt - text;
			Edit_SetSel(*m_pWindow, 0, nSize);
		}
		else
		{
			int nSize = GetWindowTextLength(*m_pWindow);
			if( nSize == 0 )
				nSize = 1;

			Edit_SetSel(*m_pWindow, 0, nSize);		
		}
	}
}