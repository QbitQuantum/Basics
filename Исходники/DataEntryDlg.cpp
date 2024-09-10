void CDataEntryDlg::ActiveEntryModePage(int nMode)
{
	CTabPage* pPage = m_apPages[nMode];
	if (pPage == NULL)
	{
		switch (nMode)
		{
		case 0:
		case 2:
			pPage = new CNumericEntryPage;
			((CNumericEntryPage *)pPage)->m_pExpert = m_pExpert;
			break;
		case 1:
			break;
		case 3:
			pPage = new CPushbuttonEntryPage;
			((CPushbuttonEntryPage *)pPage)->m_pExpert = m_pExpert;
			break;
		default:
			break;
		}

		m_apPages[nMode] = pPage;

		if (pPage != NULL)
		{
			CWindow winRect;
			winRect.Attach(GetDlgItem(IDC_RECT));
			RECT rc;
			winRect.GetWindowRect(&rc);
			ScreenToClient(&rc);
			
			pPage->Create(m_hWnd);
			rc.bottom -= 4;
			pPage->MoveTo(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		}
	}

	switch (nMode)
	{
	case 0:
	case 2:
		((CNumericEntryPage *)pPage)->m_strScript = m_pExpert->m_strActionScript;
		break;
	case 1:
		break;
	case 3:
		((CPushbuttonEntryPage *)pPage)->m_strScript = m_pExpert->m_strActionScript;
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 4; i++)
	{
		pPage = m_apPages[i];
		if (pPage != NULL)
			pPage->Show(nMode == i);
	}
		
}